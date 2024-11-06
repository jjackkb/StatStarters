#include <ncurses.h>

#include "term.h"
#include "strings.h"

Term::Term()
{

  initscr();
  curs_set(0);
  cbreak();
  noecho();

  int height = LINES;
  int width = COLS;

  mvprintw(0, 0, "test");

  this->win = newwin(height, width, 0, 0);

  paint(0, (width / 2) - (STATSTARTERS_LOGO[0].length() / 2), STATSTARTERS_LOGO);

  refresh();
  wrefresh(win);
};

void Term::paint(int x, int y, std::vector<std::string> graphic)
{

  for (int i = 0; i < graphic.size(); i++)
  {

    mvwprintw(win, x + i, y, "%s", graphic[i].c_str());
  }
}

int Term::kill_window()
{

  getch();
  delwin(win);
  endwin();

  return 0;
}