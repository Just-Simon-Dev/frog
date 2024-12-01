#include <iostream>
#include <ncurses.h>
#include "./utils/map.h"
#include "./frog/frog.h"
#include "utils/interface.h"

int main()
{
    Map* map = map_create();
    Frog* frog = frog_create();
    play_time_t* time = time_create();
    level_t* level = level_create();
    
    setFrog(frog, map);
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    
    while (true)
    {
        print_map_fixed(map);

        const int key = getch();
        if (key == 'q') break;

        clearPrevPositionOfFrog(frog, map);
        frog_movement(frog, key);
        setFrog(frog, map);

        print_time(time);
        print_level(level);
    }
    
    map_destroy(map);
    frog_destroy(frog);
    time_destroy(time);
    level_destroy(level);
    endwin();
    
    return 0;
}
