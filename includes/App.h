#ifndef APP_H
#define APP_H

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Fantasy.h"
#include "League.h"
#include "Ui.h"

class App {
 public:
  App();

 private:
  Fantasy *fantasy_;
};

#endif  // APP_H