#ifndef PROCESS_COMM_H
#define PROCESS_COMM_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "App.h"
#include "DisplayOutput.h"
#include "League.h"

extern League *cur_league;

void process_command(std::string);

#endif  //  PROCESS_COMM_H