//
// Created by simon on 17.11.24.
//

#ifndef FROG_STRUCT_H
#define FROG_STRUCT_H
#include <string>

struct Frog;

Frog* frog_create();
void frog_destroy(const Frog* frog);
void frog_movement(Frog* frog, int key);
void frog_set_position(Frog* frog, int x, int y);
int frog_get_x(const Frog* frog);
int frog_get_y(const Frog* frog);
int frog_get_width(const Frog* frog);
int frog_get_height(const Frog* frog);
std::string frog_get_icon(const Frog* frog);

#endif //FROG_STRUCT_H
