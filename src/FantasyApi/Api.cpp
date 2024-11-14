#include "Api.h"

std::string url_decode(const std::string &encoded) {
  /*
  Converts raw text form of fantasy.espn.api cookie values to URL form

  Parameters:
  const string: address of raw text form cookie value

  Returns:
  String: cookie value in URL form
  */

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

std::string construct_url(std::string leagueId) {
  /*
  Concatenate BASEURL with leagueId_ to get api url for league info

  Returns:
  String: url for league information api call
  */

  return BASEURL + leagueId;
}

std::string construct_url(std::string leagueId, std::string options) {
  /*
  Concatenate BASEURL, leagueId_ and options to get api url

  Parameters:
  String: end of url options, ex: "?view=mRoster" to view total league roster

  Returns:
  String: url for api call
  */

  return BASEURL + leagueId + options;
}

cpr::Response make_request(const std::string &url) {
  /*
  Make request for string url

  Parameters:
  String: full url for api call

  Returns:
  cpr::Response: from api call
  */

  cpr::Response r =
      cpr::Get(cpr::Url{url}, cpr::Cookies{{"espn_s2", url_decode(ESPN_S2)},
                                           {"SWID", url_decode(SWID)}});

  if (r.status_code == 401) {
    logError("Error accessing API. Failed authentication.");
    logError(r.text);
  }
  return r;
}

std::string parseStringOrIntField(const nlohmann::json &json,
                                  const std::string &key) {
  /*
  Retrieve value of key from json response

  Parameters:
  nlohmann::json json: api request JSON response
  String key: key to look for

  Returns:
  optional String: value of key from json response
  */

  if (!json.contains(key)) {
    logError("Warning: '" + key + "' key missing in JSON response.");
    return "NULL";
  }

  if (json[key].is_string()) {
    return json[key].get<std::string>();
  } else if (json[key].is_number_float()) {
    return std::to_string(json[key].get<float>());
  } else if (json[key].is_number()) {
    return std::to_string(json[key].get<int>());
  } else {
    logError("Warning: '" + key + "' is of an unexpected type.");
    return "NULL";
  }
}

std::string parseNestedField(const nlohmann::json &json,
                             const std::string &parent,
                             const std::string &child) {
  /*
  Retrieve value of nested key from json response

  Parameters:
  nlohmmann::json json: api request JSON response
  String parent: parent key from JSON resposne
  String child: child key from JSON response

  Returns:
  optional String: value of nested key from json response
  */

  if (json.contains(parent) && json[parent].contains(child)) {
    if (json[parent][child].is_string()) {
      return json[parent][child].get<std::string>();
    } else if (json[parent][child].is_number()) {
      return std::to_string(json[parent][child].get<int>());
    }
  } else {
    logError("Warning: '" + parent + "' or '" + child +
             "' key missing in JSON response.");
    return "NULL";
  }
  return "NULL";
}