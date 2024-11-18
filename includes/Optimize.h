#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include <string>
#include <vector>

#include "Member.h"
#include "Player.h"

std::vector<Player> matchup_disadvantage(const Member &, const Member &);

#endif  // OPTIMIZE_H