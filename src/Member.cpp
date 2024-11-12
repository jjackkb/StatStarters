#include "Member.h"

std::string memberId_ = "";
std::string memberAbbrev_ = "";

Member::Member() {}
Member::Member(std::string &memberId) : memberId_(memberId) {}
Member::Member(std::string &memberId, std::string &memberAbbrev)
    : memberId_(memberId), memberAbbrev_(memberAbbrev) {}

void Member::set_memberId(std::string &memberId) { memberId_ = memberId; }
void Member::set_memberAbbrev(std::string &memberAbbrev) {
  memberAbbrev_ = memberAbbrev;
}

std::string Member::get_memberId() { return memberId_; }
std::string Member::get_memberAbbrev() { return memberAbbrev_; }