//
// Created by simon on 01.12.24.
//

#ifndef LINES_H
#define LINES_H

#include "../cars/car.h"

struct lane_t;
struct street_t;

street_t* street_create();
void street_destroy(street_t* street);
int get_top_edge(const street_t* street, const int streetNumber, const int laneNumber);
int get_bottom_edge(const street_t* street, const int streetNumber, const int laneNumber);
car_t* get_cars(const street_t* street, const int streetNumber, const int laneNumber);
int get_number_of_cars(const street_t* street, const int streetNumber, const int laneNumber);
void add_random_cars(const street_t *streets);
int determineDirectionOfCar(car_t* cars, int carNumber);
car_t* get_car_by_coordinates(const street_t* street, const int x, const int y);

#endif //LINES_H
