//
// Created by simon on 01.12.24.
//

#ifndef LINES_H
#define LINES_H

struct lane_t;
struct street_t;

street_t* street_create();
void street_destroy(street_t* street);
int get_top_edge(const street_t* street, const int streetNumber, const int laneNumber);
int get_bottom_edge(const street_t* street, const int streetNumber, const int laneNumber);

#endif //LINES_H
