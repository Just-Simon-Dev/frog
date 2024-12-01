//
// Created by simon on 17.11.24.
//

#include "map.h"

#include <ncurses.h>
#include "../config.h"
#include "../frog/frog.h"

struct Frog;

enum icons
{
    EMPTY = -1,
    CAR = 0,
    FROG = 1
};

// This function converts icons enum to predefined characters
// EMPTY -> ' '
// CAR -> 'C' - car icon
// FROG -> 'F' - frog icon
// returns: char - character representation of the number
char icons_enum_to_char_icon(icons icon)
{
    if(icon == EMPTY) return ' ';
    if(icon == CAR) return 'C';
    if(icon == FROG) return 'F';
    return ' ';
}

struct Map
{
    icons values[MAP_WIDTH][MAP_HEIGHT];
};

Map* map_create()
{
    Map* map = new Map;
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            map->values[x][y] = EMPTY;
        }
    }
    return map;
}

void map_destroy(Map* map)
{
    delete map;
}

void print_vertical_border_of_map()
{
    printw("+");
    for (int x = 0; x < MAP_WIDTH; x++) 
    {
        printw("-");
    }
    printw("+\n");
}

void clearPrevPositionOfFrog(Frog* frog, Map* map)
{
    map->values[frog_get_x(frog)][frog_get_y(frog)] = EMPTY;
}

void setFrog(Frog* frog, Map* map)
{
    map->values[frog_get_x(frog)][frog_get_y(frog)] = FROG;
}

void print_map_fixed(Map* map)
{
    if (LINES < MAP_HEIGHT || COLS < MAP_WIDTH) {
        mvprintw(0, 0, "Terminal too small to display map!");
        refresh();
        return;
    }
    
    move((LINES - MAP_HEIGHT)/2, 0);
    print_vertical_border_of_map();
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        printw("|");
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            char char_icon = icons_enum_to_char_icon(map->values[x][y]);
            printw("%c", char_icon);
        }
        printw("|\n");
    }
    print_vertical_border_of_map();
    refresh();
}