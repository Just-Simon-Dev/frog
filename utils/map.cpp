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

void set_streets(street_t* street, Map* map)
{
    for (int i = 1; i < number_of_streets; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            map->values[j][get_top_edge(street, i, 0)] = LANE;
            map->values[j][get_bottom_edge(street, i, number_of_lanes - 1)] = LANE;
            for (int w = 0; w < number_of_lanes - 1; w++)
            {
                draw_dashed_line(map, j, get_top_edge(street, i, w));
            }
        }
    }
}

void print_destination_title(Map* map, destination_t* destination)
{
    map->values[MAP_WIDTH/2 - 1][get_destination_x(destination) / 2] = E;
    map->values[MAP_WIDTH/2][get_destination_x(destination) / 2] = N;
    map->values[MAP_WIDTH/2 + 1][get_destination_x(destination) / 2] = D; 
}

void print_with_colors(char icon, int color)
{
    attron(COLOR_PAIR(color));
    printw("%c", icon);
    attroff(COLOR_PAIR(color));
}

int get_proper_color(icons icon)
{
    if (icon == LANE) return 3;
    if (icon == CAR) return 2;
    if (icon == FROG) return 1;
    if (icon == E) return 4;
    if (icon == N) return 5;
    if (icon == D) return 6;
    return 0;
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
            int color = get_proper_color(map->values[x][y]);
            char char_icon = icons_enum_to_char_icon(map->values[x][y]);
            print_with_colors(char_icon, color);
        }
        printw("|\n");
    }
    print_vertical_border_of_map();
    refresh();
}