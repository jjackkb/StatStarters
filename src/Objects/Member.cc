#include "Member.h"

Member::Member() {}
Member::Member(std::string &memberId) : memberId_(memberId) {}
Member::Member(std::string &memberId, std::string &memberAbbrev)
    : memberId_(memberId), memberAbbrev_(memberAbbrev)
{
}

void Member::set_memberId(const std::string &memberId) { memberId_ = memberId; }
void Member::set_memberAbbrev(const std::string &memberAbbrev) { memberAbbrev_ = memberAbbrev; }
void Member::set_opponentId(const std::string &opponentId) { opponentId_ = opponentId; }
void Member::add_player(Player player)
{
  auto it = std::lower_bound(
      memberRoster_.begin(), memberRoster_.end(), player, [](const Player &a, const Player &b) {
        return std::stoi(a.get_playerLineupPos()) < std::stoi(b.get_playerLineupPos());
      });  // find insertion point for ascending order of playerLineupPos
  memberRoster_.insert(it, player);
}

std::string Member::get_memberId() const { return memberId_; }
std::string Member::get_memberAbbrev() const { return memberAbbrev_; }
std::string Member::get_opponentId() const { return opponentId_; }
std::vector<Player> Member::get_roster() const { return memberRoster_; }