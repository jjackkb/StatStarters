#ifndef APP_H
#define APP_H

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Display.h"
#include "Fantasy.h"
#include "League.h"

class App {
public:
  App();

private:
  std::unique_ptr<League> cur_league_;
  Fantasy *fantasy_;
};

#endif // APP_H