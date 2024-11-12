#include "ESPNFantasyAPI.h"

ErrorHandler error_handler_;
League *league_;

/*
Converts raw text form of fantasy.espn.api cookie values to URL form

Parameters:
const string: address of raw text form cookie value

Returns:
String: cookie value in URL form
*/
std::string url_decode(const std::string &encoded) {
  std::ostringstream decoded;
  for (size_t i = 0; i < encoded.length(); ++i) {
    if (encoded[i] == '%' && i + 2 < encoded.length()) {
      std::istringstream hexStream(encoded.substr(i + 1, 2));
      int hexValue;
      if (hexStream >> std::hex >> hexValue) {
        decoded << static_cast<char>(hexValue);
        i += 2;
      } else {
        decoded << '%';
      }
    } else if (encoded[i] == '+') {
      decoded << ' ';
    } else {
      decoded << encoded[i];
    }
  }
  return decoded.str();
}

ESPNFantasyAPI::ESPNFantasyAPI(League &league) : league_(&league) {
  std::string espn_s2_ = ESPN_S2;
  std::string swid_ = SWID;
  fetch_league_data();
}

/*
Concatenate BASEURL with leagueId_ to get api url for league info

Returns:
String: url for league information api call
*/
std::string ESPNFantasyAPI::construct_url() {
  return BASEURL + league_->get_leagueId();
}
/*
Concatenate BASEURL, leagueId_ and options to get api url

Parameters:
String: end of url options, ex: "?view=mRoster" to view total league roster

Returns:
String: url for api call
*/
std::string ESPNFantasyAPI::construct_url(std::string &options) {
  return BASEURL + league_->get_leagueId() + options;
}

/*
Make request for string url

Parameters:
String: full url for api call

Returns:
cpr::Response: from api call
*/
cpr::Response ESPNFantasyAPI::make_request(const std::string &url) {
  cpr::Response r =
      cpr::Get(cpr::Url{url}, cpr::Cookies{{"espn_s2", url_decode(ESPN_S2)},
                                           {"SWID", url_decode(SWID)}});

  if (r.status_code == 401) {
    error_handler_.logError("Error accessing API. Failed authentication.");
    error_handler_.logError(r.text);
  }
  return r;
}

/*
Retrieve value of key from json response

Parameters:
nlohmann::json json: api request JSON response
String key: key to look for

Returns:
optional String: value of key from json response
*/
std::optional<std::string>
ESPNFantasyAPI::parseStringOrIntField(const nlohmann::json &json,
                                      const std::string &key) {
  if (!json.contains(key)) {
    error_handler_.logError("Warning: '" + key +
                            "' key missing in JSON response.");
    return std::nullopt;
  }

  if (json[key].is_string()) {
    return json[key].get<std::string>();
  } else if (json[key].is_number()) {
    return std::to_string(json[key].get<int>());
  } else {
    error_handler_.logError("Warning: '" + key + "' is of an unexpected type.");
    return std::nullopt;
  }
}

/*
Retrieve value of nested key from json response

Parameters:
nlohmmann::json json: api request JSON response
String parent: parent key from JSON resposne
String child: child key from JSON response

Returns:
optional String: value of nested key from json response
*/
std::optional<std::string>
ESPNFantasyAPI::parseNestedField(const nlohmann::json &json,
                                 const std::string &parent,
                                 const std::string &child) {
  if (json.contains(parent) && json[parent].contains(child)) {
    return json[parent][child].get<std::string>();
  } else {
    error_handler_.logError("Warning: '" + parent + "' or '" + child +
                            "' key missing in JSON response.");
    return std::nullopt;
  }
}

void ESPNFantasyAPI::parse_seasonId(const nlohmann::json &json) {
  auto seasonId = parseStringOrIntField(json, "seasonId");
  if (seasonId) {
    league_->set_seasonId(*seasonId);
  }
}
void ESPNFantasyAPI::parse_scoringPeriodId(const nlohmann::json &json) {
  auto scoringPeriodId = parseStringOrIntField(json, "scoringPeriodId");
  if (scoringPeriodId) {
    league_->set_scoringPeriodId(*scoringPeriodId);
  }
}
void ESPNFantasyAPI::parse_leagueName(const nlohmann::json &json) {
  auto leagueName = parseNestedField(json, "settings", "name");
  if (leagueName) {
    league_->set_leagueName(*leagueName);
  }
}
void ESPNFantasyAPI::parse_leagueMembers(const nlohmann::json &json) {
  if (!json.contains("teams")) {
    error_handler_.logError("Warning: 'teams' key missing in JSON response.");
    return;
  }

  for (const auto &team : json["teams"]) {
    std::string id_str;
    auto teamId = parseStringOrIntField(team, "id");
    if (teamId) {
      id_str = *teamId;
    }

    if (team.contains("abbrev") && team["abbrev"].is_string()) {
      std::string abbrev = team["abbrev"].get<std::string>();
      league_->add_leagueMember(Member(id_str, abbrev));
    } else {
      error_handler_.logError(
          "Warning: 'abbrev' key missing in JSON response.");
    }
  }
}

void ESPNFantasyAPI::fetch_league_data() {
  cpr::Response r = make_request(construct_url());

  try {
    if (r.status_code == 200) {
      auto json = nlohmann::json::parse(r.text);

      parse_seasonId(json);
      parse_scoringPeriodId(json);
      parse_leagueName(json);
      parse_leagueMembers(json);

    } else {
      error_handler_.logError("Failed to fetch league data. Status code: " +
                              std::to_string(r.status_code));
      std::cout << r.text << std::endl;
    }
  } catch (const nlohmann::json::exception &e) {
    error_handler_.logError(ErrorHandler::ErrorCode::DATA_PARSE_ERROR, "");
  } catch (const std::exception &e) {
    error_handler_.logError(ErrorHandler::ErrorCode::UNKNOWN_ERROR, "");
  }
}