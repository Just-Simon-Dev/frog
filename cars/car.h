//
// Created by simon on 02.12.24.
//

#ifndef CAR_H
#define CAR_H
#include <ctime>
#include <string>

#include "../config.h"

struct car_t
{
    int y;
    int timeCooldown;
    clock_t timeCooldownStart;
    int direction; // 0 - right, 1 - left
    std::string icon;
    int width;
    int height;
};

car_t *car_create(const int y, const int direction, int number_of_cars = number_of_cars_per_lane);
void car_destroy(car_t *car);

#endif //CAR_H
