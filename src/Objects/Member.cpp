#include "Member.h"

#include <iostream>

std::string memberId_ = "";
std::string memberAbbrev_ = "";
std::vector<Player> memberRoster_;

Member::Member() {}
Member::Member(std::string &memberId) : memberId_(memberId) {}
Member::Member(std::string &memberId, std::string &memberAbbrev)
    : memberId_(memberId), memberAbbrev_(memberAbbrev) {}

// setters
void Member::set_memberId(std::string &memberId) { memberId_ = memberId; }
void Member::set_memberAbbrev(std::string &memberAbbrev) {
  memberAbbrev_ = memberAbbrev;
}
void Member::add_player(Player player) { memberRoster_.emplace_back(player); }

// getters
std::string Member::get_memberId() const { return memberId_; }
std::string Member::get_memberAbbrev() const { return memberAbbrev_; }
std::vector<Player> Member::get_roster() const { return memberRoster_; }