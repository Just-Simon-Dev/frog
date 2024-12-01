//
// Created by simon on 17.11.24.
//

#include "frog.h"
#include "../config.h"

struct Frog
{
    int x;
    int y;
};

Frog* frog_create()
{
    Frog* frog = new Frog;
    frog->x = 5;
    frog->y = 5;
    return frog;
}

void frog_destroy(Frog* frog)
{
    delete frog;
}

void frog_move(Frog* frog, int dx, int dy)
{
    if (frog->x + dx < 0 || frog->x + dx >= MAP_WIDTH) return;
    if (frog->y + dy < 0 || frog->y + dy >= MAP_HEIGHT) return;
    frog->x += dx;
    frog->y += dy;
}

void frog_set_position(Frog* frog, int x, int y)
{
    frog->x = x;
    frog->y = y;
}

int frog_get_x(Frog* frog)
{
    return frog->x;
}

int frog_get_y(Frog* frog)
{
    return frog->y;
}