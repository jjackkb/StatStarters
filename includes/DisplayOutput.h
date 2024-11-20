#ifndef DISPLAY_OUTPUT_H
#define DISPLAY_OUTPUT_H

#include <ncurses.h>
#undef OK

#include <sstream>
#include <string>

#include "League.h"
#include "Member.h"
#include "Player.h"
#include "Ui.h"

void display_output(std::string);
void display_err(std::string);
std::string output_league(League &league);
std::string output_member(Member &member);

#endif  //  DISPLAY_OUTPUT_H