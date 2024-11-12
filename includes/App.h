#ifndef APP_H
#define APP_H

#include <iostream>
#include <memory>
#include <string>

#include "Fantasy.h"
#include "League.h"

class App {
public:
  App();
  ~App();
  void display_league();

private:
  std::unique_ptr<League> cur_league_;
  Fantasy *fantasy_;
};

#endif // APP_H