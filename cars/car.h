//
// Created by simon on 02.12.24.
//

#ifndef CAR_H
#define CAR_H

struct car_t
{
    int y;
    int speed;
    int direction;
};

car_t *car_create(const int y, const int speed, const int direction);
void car_destroy(car_t *car);

#endif //CAR_H
