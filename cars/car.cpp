//
// Created by simon on 02.12.24.
//

#include "car.h"

#include <cstdlib>
#include <ncurses.h>

#include "../config.h"
#include "../services/config_service.h"

car_t *car_create(const int y, const int direction, int number_of_cars) 
{
    Config config;
    if (!parseConfig("../configs/car.txt", config)) {
        printw("Failed to load configuration.\n");
    }
    
    car_t *car = (car_t *)malloc(sizeof(car_t) * number_of_cars);

    for (int i = 0; i < number_of_cars; i++)
    {
        car[i].y = direction == 0 ? 0 : config.size_width;
        car[i].timeCooldownStart = clock();
        car[i].timeCooldown = (random() % (max_cars_time_cooldown_in_miliseconds - min_cars_time_cooldown_in_miliseconds + 1))
            + min_cars_time_cooldown_in_miliseconds;
        car[i].direction = direction;
        
        car[i].height = config.size_height;
        car[i].width = config.size_width;
        car[i].icon = config.icon;
    }
     
    return car;
}

void car_destroy(car_t *car)
{
    free(car);
}