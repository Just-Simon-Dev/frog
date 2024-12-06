//
// Created by simon on 04.12.24.
//

#include "time_functions.h"
#include "../config.h"

#include <time.h>

int get_present_time(int cooldown_time)
{
    if (cooldown_time == 0) cooldown_time = time(NULL);
    return cooldown_time;
}


bool isTimeElapsed(clock_t *lastUpdateTime, unsigned int interval) {
    clock_t currentTime = std::clock();
    // Convert milliseconds to clock ticks
    clock_t intervalTicks = interval * (CLOCKS_PER_SEC / 1000);

    if (currentTime - *lastUpdateTime >= intervalTicks) {
        *lastUpdateTime = currentTime;
        return true;
    }
    return false;
}