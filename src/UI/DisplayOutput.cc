#include "DisplayOutput.h"

void display_output(std::string output_str)
{
  std::stringstream outputLines(output_str);
  std::string line;
  int y = 0;

  clearScr();

  while (std::getline(outputLines, line)) {
    mvwprintw(subout, y++, 0, line.c_str());
  }

  refreshScreen();
}

void display_err(std::string err_str)
{
  err_str = "* " + err_str;
  mvprintw(maxRows - 2, 0, err_str.c_str());
  refreshScreen();
}

std::string output_league(League &league)
{
  std::ostringstream output;

  output << league.get_leagueName() << " (" << league.get_leagueId() << ")"
         << "\n season: " << league.get_seasonId()
         << "\n scoring period: " << league.get_scoringPeriodId() << "\n\n members:\n";

  for (Member &member : league.get_leagueMembers()) {
    output << "  " << output_member(member) << "\n";
  }

  std::string result = output.str();
  if (!result.empty() && result.back() == '\n') {
    result.pop_back();  // Removes the last '\n'
  }
  return result;
}

std::string output_member(Member &member)
{
  std::ostringstream output;
  output << member.get_memberAbbrev() << " (" << member.get_memberId()
         << ")\n Opp: " << member.get_opponentId();

  return output.str();
}