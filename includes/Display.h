#ifndef DISPLAY_H
#define DISPLAY_H

#include <sstream>
#include <string>

#include "League.h"
#include "Member.h"
#include "Optimize.h"
#include "Player.h"

std::string display_allLeague(League &);
std::string display_disadvantage(Member &, Member &);
std::string display_league(League &);
std::string display_member(Member &);
std::string display_player(Player &);

#endif  // DISPLAY_H