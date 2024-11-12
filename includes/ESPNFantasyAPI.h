#ifndef ESPNFantasyAPI_H
#define ESPNFantasyAPI_H

#include <cpr/cpr.h>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>

#include "ErrorHandler.h"
#include "League.h"

#define BASEURL                                                                \
  "https://lm-api-reads.fantasy.espn.com/apis/v3/games/ffl/seasons/2024/"      \
  "segments/0/leagues/"
#define ESPN_S2                                                                \
  "AEAuQPHDCe1hmHENca5DlLwqkOfMmg9QwnkubRLTvzHPN31qzhBnrDfBxLWC32TQaUiqKCdEts" \
  "iUFlPdQNnlf%2BVKj%2FViaJwqU2XaK6PVtwFwtU1LwE0XOpZfn3u%"                     \
  "2FuKCg8guDZUmhlvtPGGu0RNMbhy1Qr9GFBGUMNPk%"                                 \
  "2BcipleF9uyCc6kRVQ1vNrtBZsmTsG27CFpJTmPZI%"                                 \
  "2BWpTkOsDhjDrKv6kHrTEOu8Hj0Xn9XUi1uL9Ctt9l60Uhlqqx9hx2WUidSZKgeC1NZHMi0z"   \
  "2J"                                                                         \
  "d9y22QxB5PTgk%2Ffz28Ob3klAFVvjTHEuvKTEjqlRyY48fk0%3D"
#define SWID "{A64813BD-1E7D-47C5-9E17-A7B7756D49DF}"

extern ErrorHandler error_handler;

std::string url_decode(const std::string &encoded);

class ESPNFantasyAPI {
public:
  explicit ESPNFantasyAPI(League &league);

private:
  ErrorHandler error_handler_;
  League *league_;

  cpr::Response make_request(const std::string &);
  void fetch_league_data();
  std::string construct_url();
  std::string construct_url(std::string &);
  void parse_seasonId(const nlohmann::json &json);
  void parse_scoringPeriodId(const nlohmann::json &json);
  void parse_leagueName(const nlohmann::json &json);
  void parse_leagueMembers(const nlohmann::json &json);
};

#endif // ESPNFantasyAPI_H