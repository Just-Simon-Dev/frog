//
// Created by simon on 01.12.24.
//

#include "lane.h"
#include "../cars/car.h"

#include <cstdlib>
#include <ncurses.h>

#include "../config.h"

int actual_number_of_cars = 0;

struct lane_t
{
    int topEdge;
    int bottomEdge;
    car_t* cars;
    int number_of_cars;
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

    actual_number_of_cars = number_of_cars_per_lane * number_of_lanes * number_of_streets;
    
    for (int i = 1; i < number_of_streets + 1; i++)
    {
        int top_edge = i * streetHeight;
        street[i-1].lanes = (lane_t*)malloc(sizeof(lane_t) * number_of_lanes);
        
        street[i-1].lanes[0].topEdge = top_edge;
        street[i-1].lanes[0].bottomEdge = top_edge + laneHeight;
        
        street[i-1].lanes[0].cars = car_create(0, 1);
        street[i-1].lanes[0].number_of_cars = number_of_cars_per_lane;
        
        for (int j = 1; j < number_of_lanes; j++)
        {
            street[i-1].lanes[j].topEdge = street[i-1].lanes[j - 1].bottomEdge;
            street[i-1].lanes[j].bottomEdge = street[i-1].lanes[j].topEdge + laneHeight;
            street[i-1].lanes[j].cars = car_create(0, j % 2 + 1);
            street[i-1].lanes[j].number_of_cars = number_of_cars_per_lane;
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

int determineDirectionOfCar(car_t* cars, int carNumber)
{
    if (cars[carNumber].direction == 1) return MAP_WIDTH - cars[carNumber].y - 1;
    return cars[carNumber].y;
}

car_t* get_car_by_coordinates(const street_t* street, const int x, const int y)
{
    for (int i = 0; i < number_of_streets; i++)
    {
        for (int j = 0; j < number_of_lanes; j++)
        {
            int pos_middle_of_lane = (get_bottom_edge(street, i, j) + get_top_edge(street, i, j)) / 2;
            if (pos_middle_of_lane != y) continue;
            
            car_t* car = get_cars(street, i, j);
            for (int k = 0; k < get_number_of_cars(street, i, j); k++)
            {
                if (determineDirectionOfCar(car, k) == x) return &car[k];
            }
        }
    }
    return nullptr;
}

int get_number_of_cars(const street_t* street, const int streetNumber, const int laneNumber)
{
    return street[streetNumber].lanes[laneNumber].number_of_cars;
}

void add_random_cars(const street_t *streets) { 
    if (actual_number_of_cars >= max_number_of_cars_on_map) return;

    int random_street_index = rand() % number_of_streets;
    int random_lane_index = rand() % number_of_lanes;

    // Get a malloc'd array of cars from `get_cars`
    car_t *new_car_array = get_cars(streets, random_street_index, random_lane_index);
    if (new_car_array == NULL) {
        fprintf(stderr, "Failed to retrieve cars from lane.\n");
        return;
    }
    
    lane_t *target_lane = &streets[random_street_index].lanes[random_lane_index];

    car_t *expanded_cars = car_create(0, new_car_array->direction, target_lane->number_of_cars + 1);

    for (int i = 0; i < target_lane->number_of_cars; i++) {
        expanded_cars[i] = target_lane->cars[i];
    }
    
    target_lane->cars = expanded_cars;

    target_lane->number_of_cars++;
    actual_number_of_cars++;
}
