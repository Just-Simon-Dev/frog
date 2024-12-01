#include <iostream>
#include <ncurses.h>
#include "./utils/map.h"
#include "./frog/frog.h"
#include "./config.h"

int main()
{
    // Initialization phase
    Map* map = map_create();
    Frog* frog = frog_create();
    setFrog(frog, map);
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();

    // Game phase
    while (true)
    {
        print_map_fixed(map);
        int key = getch();

        clearPrevPositionOfFrog(frog, map);
        
        if (key == 'q') break;
        if (key == KEY_UP) frog_move(frog, 0, -1);
        if (key == KEY_DOWN) frog_move(frog, 0, 1);
        if (key == KEY_LEFT) frog_move(frog, -1, 0);
        if (key == KEY_RIGHT) frog_move(frog, 1, 0);

        setFrog(frog, map);
    }

    // Cleanup phase
    map_destroy(map);
    frog_destroy(frog);
    endwin();
    
    return 0;
}
