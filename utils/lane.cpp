//
// Created by simon on 01.12.24.
//

#include "lane.h"
#include "../utils/map.h"

#include <cstdlib>

#include "../config.h"


struct lane_t
{
    int topEdge;
    int bottomEdge;
};

lane_t* lanes_create(const int numberOfLanes)
{
    lane_t* lanes = (lane_t*)malloc(sizeof(lane_t) * numberOfLanes);
    int laneHeight = MAP_HEIGHT / (numberOfLanes + 2);
    for (int i = 1; i < numberOfLanes + 1; i++)
    {
        lanes[i-1].topEdge = i * laneHeight + laneHeight;
        lanes[i-1].bottomEdge = i * laneHeight;
    }
    return lanes;
}

void lanes_destroy(lane_t* lanes)
{
    free(lanes);
}

int get_top_edge(const lane_t* lane, const int laneNumber)
{
    return lane[laneNumber].topEdge;
}

int get_bottom_edge(const lane_t* lane, const int laneNumber)
{
    return lane[laneNumber].bottomEdge;
}