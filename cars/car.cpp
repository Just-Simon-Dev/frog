//
// Created by simon on 02.12.24.
//

#include "car.h"

#include <cstdlib>

car_t *car_create(const int y, const int speed, const int direction)
{
    car_t *car = (car_t *)malloc(sizeof(car_t));
    car->y = y;
    car->speed = speed;
    car->direction = direction;
    return car;
}

void car_destroy(car_t *car)
{
    free(car);
}