//
// Created by simon on 02.12.24.
//

#include "car.h"

#include <cstdlib>

#include "../config.h"

car_t *car_create(const int y, const int direction, int number_of_cars) 
{
    
    
    car_t *car = (car_t *)malloc(sizeof(car_t) * number_of_cars);

    for (int i = 0; i < number_of_cars; i++)
    {
        car[i].y = y;
        car[i].timeCooldownStart = clock();
        car[i].timeCooldown = (random() % (max_cars_time_cooldown_in_miliseconds - min_cars_time_cooldown_in_miliseconds + 1))
            + min_cars_time_cooldown_in_miliseconds;
        car[i].direction = direction;
    }
    
    return car;
}

void car_destroy(car_t *car)
{
    free(car);
}