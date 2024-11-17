#include <iostream>
#include <ncurses.h>

int main()
{
    initscr();
    clear();
    printw("Hello, world!");
    refresh();
    getch();
    endwin();
    
    return 0;
}
