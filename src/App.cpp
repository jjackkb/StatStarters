#include "App.h"

App::App()
    : cur_league_(std::make_unique<League>("2030108269")),
      fantasyApi_(nullptr) {
  if (cur_league_ != nullptr) {
    fantasyApi_ = new ESPNFantasyAPI(*cur_league_);
  } else {
    throw std::runtime_error("Failed to initialize App: cur_league_ is null.");
  }

  display_league();
}

void App::display_league() {
  std::string output = "{ " + cur_league_->get_leagueId() + " - " +
                       cur_league_->get_leagueName() + "\n" +
                       " season: " + cur_league_->get_seasonId() +
                       "\n"
                       " scoring period: " +
                       cur_league_->get_scoringPeriodId() + "\n";

  std::cout << output << std::endl;
  for (Member m : cur_league_->get_leagueMembers()) {
    std::cout << "  { " + m.get_memberAbbrev() + " - " + m.get_memberId() + " }"
              << std::endl;
  }
  std::cout << "}" << std::endl;
}

App::~App() { delete fantasyApi_; }