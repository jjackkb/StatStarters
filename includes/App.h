#ifndef APP_H
#define APP_H

#include <iostream>
#include <memory>
#include <string>

#include "ESPNFantasyAPI.h"
#include "League.h"

class App {
public:
  App();
  ~App();
  void display_league();

private:
  std::unique_ptr<League> cur_league_;
  ESPNFantasyAPI *fantasyApi_;
};

#endif // APP_H