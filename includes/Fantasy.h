#ifndef FANTASY_H
#define FANTASY_H

#include "Api.h"
#include "League.h"

class Fantasy {
public:
  explicit Fantasy(League &league);

private:
  League *league_;

  void parse_seasonId(const nlohmann::json &json);
  void parse_scoringPeriodId(const nlohmann::json &json);
  void parse_leagueName(const nlohmann::json &json);
  void parse_leagueMembers(const nlohmann::json &json);
  void parse_players(const nlohmann::json &json);
};

#endif // FANTASY_H