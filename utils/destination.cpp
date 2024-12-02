//
// Created by simon on 01.12.24.
//

#include "destination.h"

#include "lane.h"
#include "../config.h"

struct destination_t
{
    int x;
    int y;
};

destination_t* destination_create(const street_t* street)
{
    destination_t* destination = new destination_t;
    destination->x = get_top_edge(street, 0);
    destination->y = 0;
    return destination;
}

void destination_destroy(const destination_t* destination)
{
    delete destination;
}

int get_destination_x(const destination_t* destination)
{
    return destination->x;
}

int get_destination_y(const destination_t* destination)
{
    return destination->y;
}