#include <iostream>
#include <ncurses.h>
#include "./utils/map.h"
#include "./config.h"

int main()
{
    // Initialization phase
    Map* map = map_create();
    initscr();
    clear();

    // Game phase
    print_map_fixed(map);
    getch();

    // Cleanup phase
    map_destroy(map);
    endwin();
    
    return 0;
}
