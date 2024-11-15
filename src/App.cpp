#include "App.h"

App::App()
    : cur_league_(std::make_unique<League>("2030108269")), fantasy_(nullptr) {
  if (cur_league_ != nullptr) {
    fantasy_ = new Fantasy(*cur_league_);
  } else {
    throw std::runtime_error("Failed to initialize App: cur_league_ is null.");
  }

  std::cout << display_allLeague(*cur_league_) << std::endl;
}