//
// Created by simon on 08.12.24.
//

#include "tips.h"

void print_tips()
{
    mvprintw(LINES-7, COLS/2-1, "Tips:");
    mvprintw(LINES-6, COLS/2-1, "1. Use arrow keys to move the frog.");
    mvprintw(LINES-5, COLS/2-1, "2. Avoid cars.");
    mvprintw(LINES-4, COLS/2-1, "3. Get to the destination.");
    mvprintw(LINES-3, COLS/2-1, "4. Press 'q' to quit the game.");
    mvprintw(LINES-2, COLS/2-1, "5. Have fun!");
    mvprintw(LINES-1, COLS/2-1, "Szymon Soborowski 203639");
}