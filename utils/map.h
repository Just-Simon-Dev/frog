//
// Created by simon on 17.11.24.
//

#ifndef MAP_H
#define MAP_H

#include "../frog/frog.h"

struct Map;
Map* map_create();
void map_destroy(Map* map);
void clearPrevPositionOfFrog(Frog* frog, Map* map);
void setFrog(Frog* frog, Map* map);
void print_map_fixed(Map* map);

#endif //MAP_H
