//
// Created by simon on 01.12.24.
//

#ifndef LINES_H
#define LINES_H

struct lane_t;

lane_t* lanes_create(const int numberOfLanes);
void lanes_destroy(lane_t* lanes);
int get_top_edge(const lane_t* lane, const int laneNumber);
int get_bottom_edge(const lane_t* lane, const int laneNumber);


#endif //LINES_H
