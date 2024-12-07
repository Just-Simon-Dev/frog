//
// Created by simon on 17.11.24.
//

#include "map.h"

#include <ctime>
#include <ncurses.h>
#include <string>

#include "destination.h"
#include "interface.h"
#include "../config.h"
#include "../frog/frog.h"
#include "lane.h"
#include "time_functions.h"
#include "../cars/car.h"
#include "../services/notificationService.h"

struct Frog;

enum icons
{
    EMPTY = -1,
    LANE = 0,
    CAR = 1,
    FROG = 2,
    E = 3,
    N = 4,
    D = 5,
};

// This function converts icons enum to predefined characters
// EMPTY -> ' '
// CAR -> 'C' - car icon
// FROG -> 'F' - frog icon
// returns: char - character representation of the number
char icons_enum_to_char_icon(const icons icon)
{
    if(icon == EMPTY) return ' ';
    if(icon == CAR) return 'C';
    if(icon == FROG) return 'F';
    if(icon == LANE) return '-';
    if(icon == E) return 'E';
    if(icon == N) return 'N';
    if(icon == D) return 'D';
    return ' ';
}

struct Map
{
    icons values[MAP_WIDTH][MAP_HEIGHT];
};

Map* map_create()
{
    Map* map = new Map;
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            map->values[x][y] = EMPTY;
        }
    }
    return map;
}

void map_destroy(const Map* map)
{
    delete map;
}

void print_vertical_border_of_map()
{
    printw("+");
    for (int x = 0; x < MAP_WIDTH; x++) 
    {
        printw("-");
    }
    printw("+\n");
}

void clearPrevPositionOfFrog(const Frog* frog, Map* map)
{
    map->values[frog_get_x(frog)][frog_get_y(frog)] = EMPTY;
}

void setFrog(const Frog* frog, Map* map)
{
    map->values[frog_get_x(frog)][frog_get_y(frog)] = FROG;
}

void updateCarPosition(car_t* cars, int carNumber)
{
    cars[carNumber].y += 1;
    if (cars[carNumber].y >= MAP_WIDTH)
    {
        int random = rand() % 2;
        printw("random: %d choice", random);
        if (random == 0) cars[carNumber].direction = 0;
        else cars[carNumber].direction = 1;
        
        cars[carNumber].y = 0;
    }
}

int determineDirectionOfCar(car_t* cars, int carNumber)
{
    if (cars[carNumber].direction == 1) return MAP_WIDTH - cars[carNumber].y - 1;
    return cars[carNumber].y;
}

void detectCollision(Frog* frog, street_t* streets, play_time_t* play_time)
{
    int frog_x = frog_get_x(frog);
    int frog_y = frog_get_y(frog);
    
    for (int i = 0; i < number_of_streets; i++)
    {
        for (int lane = 0; lane < number_of_lanes; lane++)
        {
            car_t* cars = get_cars(streets, i, lane);
            for (int carIndex = 0; carIndex < number_of_cars; carIndex++)
            {
                int car_x = determineDirectionOfCar(cars, carIndex);
                int car_y = (get_bottom_edge(streets, i, lane) + get_top_edge(streets, i, lane)) / 2;
                
                if (frog_x == car_x && frog_y == car_y)
                {
                    bool choice = showPopup("You lost! Do you want to play again?");
                    if (choice)
                    {
                        frog_set_position(frog, MAP_WIDTH / 2, MAP_HEIGHT - 1);
                        reset_time(play_time);
                    }
                    else
                    {
                        endwin();
                        exit(0);
                    }
                }
            }
        }
    }
}

void increase_speed_of_cars(street_t* streets, level_t* level)
{
    for (int i = 0; i < number_of_streets; i++)
    {
        for (int lane = 0; lane < number_of_lanes; lane++)
        {
            car_t* cars = get_cars(streets, i, lane);
            for (int carIndex = 0; carIndex < number_of_cars; carIndex++)
            {
                if ( cars[carIndex].timeCooldown - level_get(level) * level_multiplier >= min_cars_time_cooldown_in_miliseconds)
                    cars[carIndex].timeCooldown -= level_get(level) * level_multiplier;
            }
        }
    }
}

void checkIfFrogReachedDestination(Frog* frog, destination_t* destination, play_time_t* play_time, level_t* level, street_t* streets)
{
    if (frog_get_y(frog) == get_destination_x(destination))
    {
        bool choice = showPopup("You won! Do you want to play again?");
        if (choice)
        {
            frog_set_position(frog, MAP_WIDTH / 2, MAP_HEIGHT - 1);
            reset_time(play_time);
            level_increase(level);
            increase_speed_of_cars(streets, level);
        }
        else
        {
            endwin();
            exit(0);
        }
    }
}

void setCars(street_t* street, int streetNumber, Map* map)
{
    for (int i = 0; i < number_of_lanes; i++)
    {
        int pos_middle_of_lane = (get_bottom_edge(street, streetNumber, i) + get_top_edge(street, streetNumber, i)) / 2;
        
        car_t* cars = get_cars(street, streetNumber, i);
        for (int j = 0; j < number_of_cars; j++)
        {
            if (isTimeElapsed(&cars[j].timeCooldownStart, cars[j].timeCooldown))
            {
                map->values[determineDirectionOfCar(cars, j)][pos_middle_of_lane] = EMPTY;
                updateCarPosition(cars, j);
                map->values[determineDirectionOfCar(cars, j)][pos_middle_of_lane] = CAR;
            }
        }
    }
}

void draw_dashed_line(Map* map, int j, int i)
{
    if (j % 2 == 0) return;
    map->values[j][i] = LANE;
}

void set_streets(street_t* street, Map* map)
{
    for (int i = 0; i < number_of_streets; i++)
    {
        
        setCars(street, i, map);
        
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            map->values[j][get_top_edge(street, i, 0)] = LANE;
            map->values[j][get_bottom_edge(street, i, number_of_lanes - 1)] = LANE;
            for (int w = 0; w < number_of_lanes - 1; w++)
            {
                draw_dashed_line(map, j, get_bottom_edge(street, i, w));
            }
        }
    }
}

void print_destination_title(Map* map, destination_t* destination)
{
    map->values[MAP_WIDTH/2 - 1][get_destination_x(destination) / 2] = E;
    map->values[MAP_WIDTH/2][get_destination_x(destination) / 2] = N;
    map->values[MAP_WIDTH/2 + 1][get_destination_x(destination) / 2] = D; 
}

void print_with_colors(char icon, int color)
{
    attron(COLOR_PAIR(color));
    printw("%c", icon);
    attroff(COLOR_PAIR(color));
}

int get_proper_color(icons icon)
{
    if (icon == LANE) return 3;
    if (icon == CAR) return 2;
    if (icon == FROG) return 1;
    if (icon == E) return 4;
    if (icon == N) return 5;
    if (icon == D) return 6;
    return 0;
}

void print_map_fixed(const Map* map)
{
    if (LINES < MAP_HEIGHT || COLS < MAP_WIDTH) {
        mvprintw(0, 0, "Terminal too small to display map!");
        refresh();
        return;
    }
    
    move((LINES - MAP_HEIGHT)/2, 0);
    print_vertical_border_of_map();
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        printw("|");
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int color = get_proper_color(map->values[x][y]);
            char char_icon = icons_enum_to_char_icon(map->values[x][y]);
            print_with_colors(char_icon, color);
        }
        printw("|\n");
    }
    print_vertical_border_of_map();
    refresh();
}