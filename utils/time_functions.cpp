//
// Created by simon on 04.12.24.
//

#include "time_functions.h"
#include "../config.h"

#include <time.h>

bool cooldown(int start_time, int seconds)
{
    return time(NULL) - start_time >= seconds;
}

int get_present_time(int cooldown_time)
{
    if (cooldown_time == 0) cooldown_time = time(NULL);
    return cooldown_time;
}

int reset_present_time(int cooldown_time)
{
    if (cooldown(cooldown_time, cars_time_cooldown_in_seconds)) cooldown_time = 0;
    return cooldown_time;
}