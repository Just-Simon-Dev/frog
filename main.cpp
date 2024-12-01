#include <iostream>
#include <ncurses.h>
#include "./utils/map.h"
#include "./frog/frog.h"

int main()
{
    Map* map = map_create();
    Frog* frog = frog_create();
    setFrog(frog, map);
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    
    while (true)
    {
        print_map_fixed(map);

        const int key = getch();
        if (key == 'q') break;

        clearPrevPositionOfFrog(frog, map);
        frog_movement(frog, key);
        setFrog(frog, map);
    }
    
    map_destroy(map);
    frog_destroy(frog);
    endwin();
    
    return 0;
}
