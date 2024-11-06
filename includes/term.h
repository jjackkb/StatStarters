#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>

class Term
{

public:
  Term();
  int kill_window();

private:
  WINDOW *win;

  void paint(int, int, std::vector<std::string>);
};

#endif // TERM_H