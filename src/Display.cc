#include "Display.h"

std::string display_allLeague(League &league)
{
  std::ostringstream output;

  output << league.get_leagueName() << " (" << league.get_leagueId() << ")"
         << "\n season: " << league.get_seasonId()
         << "\n scoring period: " << league.get_scoringPeriodId() << "\n members:\n\n";

  for (Member &member : league.get_leagueMembers()) {
    std::string memberOutput = display_member(member);
    std::istringstream memberLines(memberOutput);
    std::string line;
    while (std::getline(memberLines, line)) {
      output << "  " << line << "\n";
    }
    output << "\n";

    for (Player &player : member.get_roster()) {
      std::string playerOutput = display_player(player);
      std::istringstream playerLines(playerOutput);
      std::string line;
      while (std::getline(playerLines, line)) {
        output << "     " << line << "\n";
      }
      output << "\n";
    }
  }

  std::string result = output.str();
  if (!result.empty() && result.back() == '\n') {
    result.pop_back();
    result.pop_back();  // Removes the last two '\n'
  }
  return result;
}

std::string display_league(League &league)
{
  std::ostringstream output;

  output << league.get_leagueName() << " (" << league.get_leagueId() << ")"
         << "\n season: " << league.get_seasonId()
         << "\n scoring period: " << league.get_scoringPeriodId() << "\n\n members:\n";

  for (Member &member : league.get_leagueMembers()) {
    output << "  " << display_member(member) << "\n";
  }

  std::string result = output.str();
  if (!result.empty() && result.back() == '\n') {
    result.pop_back();  // Removes the last '\n'
  }
  return result;
}
std::string display_member(Member &member)
{
  std::ostringstream output;
  output << member.get_memberAbbrev() << " (" << member.get_memberId()
         << ")\n Opp: " << member.get_opponentId();

  return output.str();
}

std::string display_player(Player &player)
{
  std::ostringstream output;

  output << player.get_playerName() << " (" << player.get_playerId() << ")"
         << "\n  position: " << player.get_playerPos()
         << "\n  lineup slot: " << player.get_playerLineupPos()
         << "\n  projected: " << player.get_playerProj()
         << "\n  average: " << player.get_playerAvg();
  return output.str();
}