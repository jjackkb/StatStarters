#ifndef UI_H
#define UI_H

#include <ncurses.h>
#undef OK

#include <sstream>

#include "ProcessComm.h"

extern bool init, quit;
extern int maxRows, maxCols;

extern WINDOW* subout;

void initialize();
void refreshScreen();
void clearScr();
void clearInput();
void getInput();
void destroy();

#endif  // UI_H