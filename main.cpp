#include <iostream>
#include <ncurses.h>

#include "config.h"
#include "./utils/map.h"
#include "./frog/frog.h"
#include "utils/interface.h"
#include "utils/lane.h"
#include "utils/destination.h"

int main()
{
    Map* map = map_create();
    Frog* frog = frog_create();
    play_time_t* time = time_create();
    level_t* level = level_create();
    street_t* streets = street_create();
    destination_t* destination = destination_create(streets);
    
    setFrog(frog, map);
    
    initscr();
    if (has_colors())
    {
        start_color();
    }
    
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    while (true)
    {
        print_map_fixed(map);
        print_destination_title(map, destination);
        
        const int key = getch();
        if (key == 'q') break;

        clearPrevPositionOfFrog(frog, map);
        frog_movement(frog, key);
        set_streets(streets, map);
        setFrog(frog, map);
        detectCollision(frog, streets, time);
        
        print_time(time);
        print_level(level);
    }
    
    map_destroy(map);
    frog_destroy(frog);
    time_destroy(time);
    level_destroy(level);
    destination_destroy(destination);
    street_destroy(streets);
    
    endwin();
    
    return 0;
}
