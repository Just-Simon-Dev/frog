//
// Created by simon on 17.11.24.
//

#ifndef MAP_H
#define MAP_H

#include <ctime>

#include "../frog/frog.h"
#include "lane.h"
#include "destination.h"
#include "interface.h"

struct Map;
Map* map_create();
void map_destroy(const Map* map);
void clearPrevPositionOfFrog(const Frog* frog, Map* map);
void setFrog(const Frog* frog, Map* map);
void set_streets(street_t* street, Map* map);
void print_destination_title(Map* map, destination_t* destination);
void print_map_fixed(const Map* map);
void detectCollision(Frog* frog, street_t* streets, play_time_t* play_time);
void checkIfFrogReachedDestination(Frog* frog, destination_t* destination, play_time_t* play_time, level_t* level, street_t* streets);

#endif //MAP_H
