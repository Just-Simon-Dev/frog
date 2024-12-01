//
// Created by simon on 17.11.24.
//

#ifndef MAP_H
#define MAP_H

#include "../frog/frog.h"
#include "lane.h"

struct Map;
Map* map_create();
void map_destroy(const Map* map);
void clearPrevPositionOfFrog(const Frog* frog, Map* map);
void setFrog(const Frog* frog, Map* map);
void set_lanes(lane_t* lanes, Map* map);
void print_map_fixed(const Map* map);

#endif //MAP_H
