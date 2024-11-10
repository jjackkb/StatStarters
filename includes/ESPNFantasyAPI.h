#ifndef ESPNFantasyAPI_H
#define ESPNFantasyAPI_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <iomanip>

#define BASEURL "https://lm-api-reads.fantasy.espn.com/apis/v3/games/ffl/seasons/2024/segments/0/leagues/"

std::string url_decode(const std::string &encoded);

class ESPNFantasyAPI
{

public:
  ESPNFantasyAPI(const std::string &leagueId);
  std::string get_league_id();

private:
  std::string baseUrl;
  std::string leagueId_;
  std::string leagueName_;

  void fetch_league_data();
};

#endif // ESPNFantasyAPI_H