#ifndef ESPNFantasyAPI_H
#define ESPNFantasyAPI_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>

#define BASEURL "https://lm-api-reads.fantasy.espn.com/apis/v3/games/ffl/seasons/2024/segments/0/leagues/"

std::string url_decode(const std::string &encoded);

class ESPNFantasyAPI
{

public:
  ESPNFantasyAPI(const std::string &leagueId);
  std::string get_league_name();
  std::vector<std::pair<std::string, std::string>> get_league_memebers();

private:
  std::string baseUrl;
  std::string leagueId_;
  std::string leagueName_;
  std::vector<std::pair<std::string, std::string>> leagueMembers_; // {TEAM_ID, TEAM_ABBREV}

  void fetch_league_data();
};

#endif // ESPNFantasyAPI_H