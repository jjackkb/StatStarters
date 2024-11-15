#ifndef MEMBER_H
#define MEMBER_H

#include <algorithm>
#include <string>
#include <vector>

#include "Player.h"

class Member {
public:
  Member();
  Member(std::string &);
  Member(std::string &, std::string &);

  void set_memberId(std::string &);
  void set_memberAbbrev(std::string &);
  void add_player(Player player);

  std::string get_memberId() const;
  std::string get_memberAbbrev() const;
  std::vector<Player> get_roster() const;

private:
  std::string memberId_;
  std::string memberAbbrev_;
  std::vector<Player> memberRoster_;
};

#endif // MEMBER_H