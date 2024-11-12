#include "ESPNFantasyAPI.h"

ErrorHandler error_handler_;
League *league_;

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

std::string ESPNFantasyAPI::construct_url() {
  return BASEURL + league_->get_leagueId();
}
std::string ESPNFantasyAPI::construct_url(std::string &options) {
  return BASEURL + league_->get_leagueId() + options;
}

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

void ESPNFantasyAPI::parse_seasonId(const nlohmann::json &json) {
  if (json.contains("seasonId")) {
    if (json["seasonId"].is_string()) {
      league_->set_seasonId(json["seasonId"].get<std::string>());
    } else if (json["seasonId"].is_number()) {
      league_->set_seasonId(std::to_string(json["seasonId"].get<int>()));
    } else {
      error_handler_.logError("Warning: 'seasonId' is of an unexpected type.");
    }
  } else {
    error_handler_.logError("Warning:'seasonId' key "
                            "missing in JSON response.");
  }
}
void ESPNFantasyAPI::parse_scoringPeriodId(const nlohmann::json &json) {
  if (json.contains("scoringPeriodId")) {
    if (json["scoringPeriodId"].is_string()) {
      league_->set_scoringPeriodId(json["scoringPeriodId"].get<std::string>());
    } else if (json["scoringPeriodId"].is_number()) {
      league_->set_scoringPeriodId(
          std::to_string(json["scoringPeriodId"].get<int>()));
    } else {
      error_handler_.logError(
          "Warning: 'scoringPeriodId' is of an unexpected type.");
    }
  } else {
    error_handler_.logError("Warning: 'settings' or 'scoringPeriodId' key "
                            "missing in JSON response.");
  }
};
void ESPNFantasyAPI::parse_leagueName(const nlohmann::json &json) {
  if (json.contains("settings") && json["settings"].contains("name")) {
    league_->set_leagueName(json["settings"]["name"].get<std::string>());

  } else {
    error_handler_.logError(
        "Warning: 'settings' or 'name' key missing in JSON response.");
  }
};
void ESPNFantasyAPI::parse_leagueMembers(const nlohmann::json &json) {
  if (json.contains("teams")) {
    for (const auto &team : json["teams"]) {
      std::string id_str;
      if (team.contains("id")) {
        if (team["id"].is_string()) {
          id_str = team["id"].get<std::string>();
        } else if (team["id"].is_number()) {
          id_str = std::to_string(team["id"].get<int>());
        } else {
          error_handler_.logError("Warning: 'id' is of an unexpected type.");
        }
      }

      if (team.contains("abbrev") && team["abbrev"].is_string()) {
        std::string abbrev = team["abbrev"].get<std::string>();

        league_->add_leagueMember(Member(id_str, abbrev));
      } else {
        error_handler_.logError("Warning: 'abbrev' key missing or not a "
                                "string for a team in JSON response.");
      }
    }
  } else {
    error_handler_.logError("Warning: 'teams' key missing in JSON response.");
  }
}

void ESPNFantasyAPI::fetch_league_data() {
  /* DEBUG
  std::cout << construct_url() << std::endl;
  // */

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