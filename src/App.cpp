#include "App.h"

App::App()
    : cur_league_(std::make_unique<League>("2030108269")), fantasy_(nullptr) {
  if (cur_league_ != nullptr) {
    fantasy_ = new Fantasy(*cur_league_);
  } else {
    throw std::runtime_error("Failed to initialize App: cur_league_ is null.");
  }

  display_league();
}

void App::display_league() {
  std::ostringstream output;
  output << "{ " << cur_league_->get_leagueId() << " - "
         << cur_league_->get_leagueName()
         << "\n season: " << cur_league_->get_seasonId()
         << "\n scoring period: " << cur_league_->get_scoringPeriodId() << "\n";

  std::cout << output.str() << std::endl;

  const auto &league_members = cur_league_->get_leagueMembers();
  for (const Member &m : league_members) {
    std::cout << "  { " << m.get_memberAbbrev() << " - " << m.get_memberId()
              << std::endl;
    std::cout << display_players(m) << std::endl;
  }
  std::cout << "}" << std::endl;
}

std::string App::display_players(const Member &member) {
  std::ostringstream output;
  output << "   {\n";

  for (Player &player : member.get_roster()) {
    output << "    " << player.get_playerName() << " (" << player.get_playerId()
           << ")"
           << "\n      Position: " << player.get_playerPos()
           << "\n      Projected: " << player.get_playerProj() << "\n";
  }

  output << "   }\n  }";
  return output.str();
}

App::~App() { delete fantasy_; }