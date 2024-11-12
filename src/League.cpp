#include "League.h"
#include <iostream>

std::string leagueId_ = "";
std::string seasonId_ = "";
std::string scoringPeriodId_ = "";
std::string leagueName_ = "";
std::vector<Member *> leagueMembers_ = {}; // {TEAM_ID, TEAM_ABBREV}

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
void League::add_leagueMember(Member member) {
  leagueMembers_.emplace_back(member);
}

std::string League::get_leagueId() {
  return leagueId_.empty() ? "NULL" : leagueId_;
}
std::string League::get_seasonId() {
  return seasonId_.empty() ? "NULL" : seasonId_;
}
std::string League::get_scoringPeriodId() {
  return scoringPeriodId_.empty() ? "NULL" : scoringPeriodId_;
}
std::string League::get_leagueName() {
  return leagueName_.empty() ? "NULL" : leagueName_;
}
std::vector<Member> League::get_leagueMembers() { return leagueMembers_; }
