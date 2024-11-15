#include "League.h"
#include <iostream>

League::League() {}
League::League(const std::string &leagueId) : leagueId_(leagueId) {}

void League::set_leagueId(const std::string &leagueId) { leagueId_ = leagueId; }
void League::set_seasonId(const std::string &seasonId) { seasonId_ = seasonId; }
void League::set_scoringPeriodId(const std::string &scoringPeriodId) {
  scoringPeriodId_ = scoringPeriodId;
}
void League::set_leagueName(const std::string &leagueName) {
  leagueName_ = leagueName;
}
void League::add_leagueMember(const Member &member) {
  leagueMembers_.emplace_back(member);
}

std::string League::get_leagueId() const {
  return leagueId_.empty() ? "NULL" : leagueId_;
}
std::string League::get_seasonId() const {
  return seasonId_.empty() ? "NULL" : seasonId_;
}
std::string League::get_scoringPeriodId() const {
  return scoringPeriodId_.empty() ? "NULL" : scoringPeriodId_;
}
std::string League::get_leagueName() const {
  return leagueName_.empty() ? "NULL" : leagueName_;
}
std::vector<Member> &League::get_leagueMembers() { return leagueMembers_; }
