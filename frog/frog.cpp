//
// Created by simon on 17.11.24.
//

#include "frog.h"

#include <cstring>
#include <ctime>
#include <ncurses.h>
#include <stdlib.h>

#include "../config.h"
#include "../services/config_service.h"
#include "../utils/time_functions.h"

struct Frog
{
    int x;
    int y;
    int width;
    int height;
    std::string icon;
    clock_t moveStart;
};

Frog* frog_create()
{
    Config config;
    if (!parseConfig("../configs/frog.txt", config)) {
        printw("Failed to load configuration.\n");
    }
    
    Frog* frog = new Frog;
    frog->x = MAP_WIDTH / 2;
    frog->y = MAP_HEIGHT - 1;
    frog->moveStart = clock();

    frog->height = config.size_height;
    frog->width = config.size_width;
    frog->icon = config.icon.c_str();
    
    return frog;
}

void frog_destroy(const Frog* frog)
{
    delete frog;
}

void frog_move(Frog* frog, const int dx, const int dy)
{
    if (!isTimeElapsed(&frog->moveStart, frog_move_cooldown_in_miliseconds)) return;
    if (frog->x + dx < 0 || frog->x + dx >= MAP_WIDTH) return;
    if (frog->y + dy < 0 || frog->y + dy >= MAP_HEIGHT) return;
    frog->x += dx;
    frog->y += dy;
}

void frog_movement(Frog* frog, const int key)
{
    if (key == KEY_UP) frog_move(frog, 0, -1);
    if (key == KEY_DOWN) frog_move(frog, 0, 1);
    if (key == KEY_LEFT) frog_move(frog, -1, 0);
    if (key == KEY_RIGHT) frog_move(frog, 1, 0); 
}


void frog_set_position(Frog* frog, const int x, const int y)
{
    frog->x = x;
    frog->y = y;
}

int frog_get_x(const Frog* frog)
{
    return frog->x;
}

int frog_get_y(const Frog* frog)
{
    return frog->y;
}

int frog_get_width(const Frog* frog)
{
    return frog->width;
}

int frog_get_height(const Frog* frog)
{
    return frog->height;
}

std::string frog_get_icon(const Frog* frog)
{
    return frog->icon;
}