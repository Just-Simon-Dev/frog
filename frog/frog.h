//
// Created by simon on 17.11.24.
//

#ifndef FROG_STRUCT_H
#define FROG_STRUCT_H

struct Frog;

Frog* frog_create();
void frog_destroy(Frog* frog);
void frog_movement(Frog* frog, int key);
void frog_set_position(Frog* frog, int x, int y);
int frog_get_x(Frog* frog);
int frog_get_y(Frog* frog);

#endif //FROG_STRUCT_H
