#include "Ui.h"

bool init = 0;
bool quit = 0;
int maxRows = 0;
int maxCols = 0;
WINDOW* subout = nullptr;

void initialize()
{
  initscr();
  cbreak();
  noecho();
  curs_set(1);
  getmaxyx(stdscr, maxRows, maxCols);

  subout = subwin(stdscr, maxRows - 1, maxCols - 1, 0, 0);

  move(maxRows - 1, 0);
  addch(':');

  refreshScreen();
  init = 1;

  getInput();
}

void refreshScreen()
{
  refresh();
  wrefresh(subout);
  move(maxRows - 1, 1);
}

void clearScr()
{
  clear();
  move(maxRows - 1, 0);
  addch(':');
  refreshScreen();
}

void clearInput()
{
  move(maxRows - 1, 0);
  clrtoeol();
  addch(':');
  refreshScreen();
}

void getInput()
{
  std::ostringstream input;
  while (init == 1 && quit == 0) {
    int c = getch();
    if (c == KEY_BACKSPACE || c == 127 || c == '\b') {
      if (!input.str().empty()) {
        std::string temp = input.str();
        temp.pop_back();
        input.str("");
        input.clear();
        input << temp;

        int y, x;
        getyx(stdscr, y, x);
        if (x > 0) {
          move(y, x - 1);
          addch(' ');
          move(y, x - 1);
        }
      }
    }
    else if (c != 10) {
      input << static_cast<char>(c);
      addch(c);
    }
    else {
      process_command(input.str());
      input.str("");
      input.clear();
    }
  }

  if (quit == 1) {
    clear();
    refreshScreen();
    destroy();
  }
}

void destroy() { endwin(); }