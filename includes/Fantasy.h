#ifndef FANTASY_H
#define FANTASY_H

#include "Api.h"
#include "League.h"

class Fantasy {
 public:
  explicit Fantasy(League &);

 private:
  League *league_;

  void parse_seasonId(const nlohmann::json &);
  void parse_scoringPeriodId(const nlohmann::json &);
  void parse_leagueName(const nlohmann::json &);
  void parse_leagueMembers(const nlohmann::json &);
  void parse_teams(const nlohmann::json &);
  void parse_team(const nlohmann::json &);
  void parse_roster(const nlohmann::json &, Member &);
  void parse_player(const nlohmann::json &, Member &);
  void parse_playerStats(const nlohmann::json &, Player &);
  void parse_matchups(const nlohmann::json &);
};

#endif  // FANTASY_H