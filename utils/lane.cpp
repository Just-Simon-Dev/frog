//
// Created by simon on 01.12.24.
//

#include "lane.h"
#include "../cars/car.h"

#include <cstdlib>

#include "../config.h"


struct lane_t
{
    int topEdge;
    int bottomEdge;
    car_t* cars;
};

struct street_t
{
    
    lane_t* lanes;
};

street_t* street_create()
{
    street_t* street = (street_t*)malloc(sizeof(street_t) * number_of_streets);
    int streetHeight = MAP_HEIGHT / (number_of_streets + 2);
    int laneHeight = streetHeight / number_of_lanes;
    for (int i = 1; i < number_of_streets + 1; i++)
    {
        int top_edge = i * streetHeight;
        street[i-1].lanes = (lane_t*)malloc(sizeof(lane_t) * number_of_lanes);
        
        street[i-1].lanes[0].topEdge = top_edge;
        street[i-1].lanes[0].bottomEdge = top_edge + laneHeight;
        
        street[i-1].lanes[0].cars = car_create(0, 1);
        
        for (int j = 1; j < number_of_lanes; j++)
        {
            street[i-1].lanes[j].topEdge = street[i-1].lanes[j - 1].bottomEdge;
            street[i-1].lanes[j].bottomEdge = street[i-1].lanes[j].topEdge + laneHeight;
            street[i-1].lanes[j].cars = car_create(0, j % 2 + 1);
        }
    }
    return street;
}

void street_destroy(street_t* street)
{
    for (int i = 0; i < number_of_streets; i++)
    {
        
        for (int j = 0; j < number_of_lanes; j++)
        {
            car_destroy(street[i].lanes[j].cars);
        }
        
        free(street[i].lanes);
    }
    free(street);
    
}

int get_top_edge(const street_t* street, const int streetNumber, const int laneNumber)
{
    return street[streetNumber].lanes[laneNumber].topEdge;
}

int get_bottom_edge(const street_t* street, const int streetNumber, const int laneNumber)
{
    return street[streetNumber].lanes[laneNumber].bottomEdge;
}

car_t* get_cars(const street_t* street, const int streetNumber, const int laneNumber)
{
    return street[streetNumber].lanes[laneNumber].cars;
}