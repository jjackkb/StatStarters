#include "ESPNFantasyAPI.h"

std::string espn_s2 = "AEAuQPHDCe1hmHENca5DlLwqkOfMmg9QwnkubRLTvzHPN31qzhBnrDfBxLWC32TQaUiqKCdEtsiUFlPdQNnlf%2BVKj%2FViaJwqU2XaK6PVtwFwtU1LwE0XOpZfn3u%2FuKCg8guDZUmhlvtPGGu0RNMbhy1Qr9GFBGUMNPk%2BcipleF9uyCc6kRVQ1vNrtBZsmTsG27CFpJTmPZI%2BWpTkOsDhjDrKv6kHrTEOu8Hj0Xn9XUi1uL9Ctt9l60Uhlqqx9hx2WUidSZKgeC1NZHMi0z2Jd9y22QxB5PTgk%2Ffz28Ob3klAFVvjTHEuvKTEjqlRyY48fk0%3D";
std::string SWID = "{A64813BD-1E7D-47C5-9E17-A7B7756D49DF}";
std::string leagueId_;
std::string leagueName_;

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
  std::cout << leagueName_ << std::endl;
}

void ESPNFantasyAPI::fetch_league_data()
{

  std::string url = BASEURL + leagueId_;
  cpr::Response r = cpr::Get(cpr::Url{url},
                             cpr::Cookies{
                                 {"SWID", url_decode(SWID)},
                                 {"espn_s2", url_decode(espn_s2)}});

  if (r.status_code == 200)
  {
    auto json = nlohmann::json::parse(r.text);
    if (!json.empty())
    {
      leagueName_ = json["settings"]["name"].get<std::string>();
    }
  }
  else
  {
    std::cerr << "Failed to fetch league data. Status code: " + std::to_string(r.status_code) << std::endl;
  }
}
