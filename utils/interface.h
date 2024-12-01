//
// Created by simon on 01.12.24.
//

#ifndef INTERFACE_H
#define INTERFACE_H

struct play_time_t;
struct level_t;

play_time_t* time_create();
void time_destroy(const play_time_t* time);
int time_get_elapsed(const play_time_t* time);
void print_time(const play_time_t* time);
void reset_time(play_time_t* time);

level_t* level_create();
void level_destroy(const level_t* level);
int level_get(const level_t* level);
void level_increase(level_t* level);
void print_level(const level_t* level);


#endif //INTERFACE_H
