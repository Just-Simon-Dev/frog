//
// Created by simon on 04.12.24.
//

#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H
#include <ctime>

int get_present_time(int cooldown_time);
int reset_present_time(int cooldown_time);
bool isTimeElapsed(clock_t *lastUpdateTime, unsigned int interval);

#endif //TIME_FUNCTIONS_H
