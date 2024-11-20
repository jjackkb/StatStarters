#ifndef FANTASY_H
#define FANTASY_H

class League;
class Member;
class Player;

#include <nlohmann/json.hpp>

#include "Api.h"

class Fantasy {
 public:
  League *league_;

  explicit Fantasy(League &league);
  void retrieve_leagueInfo();
  void retrieve_roster();
  void retrieve_matchup();

 private:
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