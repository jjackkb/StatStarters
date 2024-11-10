#include "ESPNFantasyAPI.h"

std::string espn_s2 = "AEAuQPHDCe1hmHENca5DlLwqkOfMmg9QwnkubRLTvzHPN31qzhBnrDfBxLWC32TQaUiqKCdEtsiUFlPdQNnlf%2BVKj%2FViaJwqU2XaK6PVtwFwtU1LwE0XOpZfn3u%2FuKCg8guDZUmhlvtPGGu0RNMbhy1Qr9GFBGUMNPk%2BcipleF9uyCc6kRVQ1vNrtBZsmTsG27CFpJTmPZI%2BWpTkOsDhjDrKv6kHrTEOu8Hj0Xn9XUi1uL9Ctt9l60Uhlqqx9hx2WUidSZKgeC1NZHMi0z2Jd9y22QxB5PTgk%2Ffz28Ob3klAFVvjTHEuvKTEjqlRyY48fk0%3D";
std::string SWID = "{A64813BD-1E7D-47C5-9E17-A7B7756D49DF}";
std::string leagueId_;
std::string leagueName_;
std::vector<std::pair<std::string, std::string>> leagueMembers_; // {TEAM_ID, TEAM_ABBREV}

std::string url_decode(const std::string &encoded)
{
  std::ostringstream decoded;
  for (size_t i = 0; i < encoded.length(); ++i)
  {
    if (encoded[i] == '%' && i + 2 < encoded.length())
    {
      std::istringstream hexStream(encoded.substr(i + 1, 2));
      int hexValue;
      if (hexStream >> std::hex >> hexValue)
      {
        decoded << static_cast<char>(hexValue);
        i += 2;
      }
      else
      {
        decoded << '%';
      }
    }
    else if (encoded[i] == '+')
    {
      decoded << ' ';
    }
    else
    {
      decoded << encoded[i];
    }
  }
  return decoded.str();
}

ESPNFantasyAPI::ESPNFantasyAPI(const std::string &leagueId)
    : leagueId_(leagueId)
{
  fetch_league_data();
}

void ESPNFantasyAPI::fetch_league_data()
{
  std::string url = BASEURL + leagueId_;
  cpr::Response r = cpr::Get(cpr::Url{url},
                             cpr::Cookies{
                                 {"SWID", url_decode(SWID)},
                                 {"espn_s2", url_decode(espn_s2)}});

  try
  {
    if (r.status_code == 200)
    {
      auto json = nlohmann::json::parse(r.text);

      if (json.contains("settings") && json["settings"].contains("name"))
      {
        leagueName_ = json["settings"]["name"].get<std::string>();
      }
      else
      {
        std::cerr << "Warning: 'settings' or 'name' key missing in JSON response.\n";
      }

      if (json.contains("teams"))
      {
        for (const auto &team : json["teams"])
        {
          std::string id_str;
          if (team.contains("id"))
          {
            if (team["id"].is_string())
            {
              id_str = team["id"].get<std::string>();
            }
            else if (team["id"].is_number())
            {
              id_str = std::to_string(team["id"].get<int>());
            }
            else
            {
              std::cerr << "Warning: 'id' is of an unexpected type.\n";
            }
          }

          if (team.contains("abbrev") && team["abbrev"].is_string())
          {
            std::string abbrev = team["abbrev"].get<std::string>();
            leagueMembers_.emplace_back(id_str, abbrev);
          }
          else
          {
            std::cerr << "Warning: 'abbrev' key missing or not a string for a team in JSON response.\n";
          }
        }
      }
      else
      {
        std::cerr << "Warning: 'teams' key missing in JSON response.\n";
      }
    }
    else
    {
      std::cerr << "Failed to fetch league data. Status code: " << r.status_code << std::endl;
    }
  }
  catch (const nlohmann::json::exception &e)
  {
    std::cerr << "JSON parsing error: " << e.what() << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Unexpected error: " << e.what() << std::endl;
  }
}

std::string ESPNFantasyAPI::get_league_name()
{
  return leagueName_;
}

std::vector<std::pair<std::string, std::string>> ESPNFantasyAPI::get_league_memebers()
{
  return leagueMembers_;
}