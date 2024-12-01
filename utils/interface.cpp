//
// Created by simon on 01.12.24.
//

#include "interface.h"

#include <ncurses.h>
#include <time.h>
#include "../config.h"

struct level_t
{
    int level;
};

struct play_time_t
{
    int startTime;
};

play_time_t* time_create()
{
    play_time_t* play_time = new play_time_t;
    play_time->startTime = time(NULL);
    return play_time;
}

void time_destroy(const play_time_t* time)
{
    delete time;
}

int time_get_elapsed(const play_time_t* play_time)
{
    return time(NULL) - play_time->startTime;
}

void print_time(const play_time_t* time)
{
    mvprintw(2, 0, "Play time: %ds", time_get_elapsed(time));
}

void reset_time(play_time_t* play_time)
{
    play_time->startTime = time(NULL);
}

level_t* level_create()
{
    level_t* level = new level_t;
    level->level = 1;
    return level;
}

void level_destroy(const level_t* level)
{
    delete level;
}

int level_get(const level_t* level)
{
    return level->level;
}

void level_increase(level_t* level)
{
    level->level++;
}

void print_level(const level_t* level)
{
    mvprintw(1, 0, "Level: %d", level_get(level));
}