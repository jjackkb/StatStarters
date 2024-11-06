#include <ncurses.h>

#include "main.h"
#include "term.h"

int main(void)
{
    Term Term;

    Term.kill_window();

    return 0;
}