//
// Created by simon on 01.12.24.
//

#ifndef DESTINATION_H
#define DESTINATION_H

#include "lane.h"

struct destination_t;

destination_t* destination_create(const street_t* street);
void destination_destroy(const destination_t* destination);
int get_destination_x(const destination_t* destination);

#endif //DESTINATION_H
