#ifndef LEAGUE_H
#define LEAGUE_H

#include <string>
#include <vector>

#include "Fantasy.h"
#include "Member.h"

class League {
 public:
  League(const std::string &);

  void set_leagueId(const std::string &);
  void set_seasonId(const std::string &);
  void set_scoringPeriodId(const std::string &);
  void set_leagueName(const std::string &);
  void add_leagueMember(const Member &);

  std::string get_leagueId() const;
  std::string get_seasonId() const;
  std::string get_scoringPeriodId() const;
  std::string get_leagueName() const;
  std::vector<Member> &get_leagueMembers();

 private:
  std::string leagueId_;
  std::string seasonId_;
  std::string scoringPeriodId_;
  std::string leagueName_;
  std::vector<Member> leagueMembers_;  // {TEAM_ID, TEAM_ABBREV}
};

#endif  // LEAGUE_H