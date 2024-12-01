//
// Created by simon on 17.11.24.
//

#include "map.h"

#include <ncurses.h>
#include <string>

#include "destination.h"
#include "../config.h"
#include "../frog/frog.h"
#include "lane.h"

struct Frog;

enum icons
{
    EMPTY = -1,
    LANE = 0,
    CAR = 1,
    FROG = 2,
    E = 3,
    N = 4,
    D = 5,
};

// This function converts icons enum to predefined characters
// EMPTY -> ' '
// CAR -> 'C' - car icon
// FROG -> 'F' - frog icon
// returns: char - character representation of the number
char icons_enum_to_char_icon(const icons icon)
{
    if(icon == EMPTY) return ' ';
    if(icon == CAR) return 'C';
    if(icon == FROG) return 'F';
    if(icon == LANE) return '-';
    if(icon == E) return 'E';
    if(icon == N) return 'N';
    if(icon == D) return 'D';
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

void map_destroy(const Map* map)
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

void clearPrevPositionOfFrog(const Frog* frog, Map* map)
{
    map->values[frog_get_x(frog)][frog_get_y(frog)] = EMPTY;
}

void setFrog(const Frog* frog, Map* map)
{
    map->values[frog_get_x(frog)][frog_get_y(frog)] = FROG;
}

void draw_dashed_line(Map* map, int j, int i)
{
    if (j % 2 == 0) return;
    map->values[j][i] = LANE;
}

void set_lanes(lane_t* lanes, Map* map)
{
    int dashed_line_pos = 0;
    for (int i = 0; i < number_of_lane; i++)
    {
        dashed_line_pos = (get_top_edge(lanes, i) + get_bottom_edge(lanes, i)) / 2;
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            
            draw_dashed_line(map, j, dashed_line_pos);
            map->values[j][get_top_edge(lanes, i)] = LANE;
            map->values[j][get_bottom_edge(lanes, i)] = LANE;
        }
    }
}

void print_destination_title(Map* map, destination_t* destination)
{
    map->values[MAP_WIDTH/2 - 1][get_destination_x(destination) / 2] = E;
    map->values[MAP_WIDTH/2][get_destination_x(destination) / 2] = N;
    map->values[MAP_WIDTH/2 + 1][get_destination_x(destination) / 2] = D; 
}

void print_map_fixed(const Map* map)
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