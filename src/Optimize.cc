#include "Optimize.h"

std::vector<Player> matchup_disadvantage(const Member &mem1, const Member &mem2)
{
  std::vector<Player> output;

  for (int i = 0; i < 8; i++) {
    if (mem1.get_roster()[i].get_playerProj() < mem2.get_roster()[i].get_playerProj()) {
      output.push_back(mem1.get_roster()[i]);
      output.push_back(mem2.get_roster()[i]);
    }
  }
  return output;
}