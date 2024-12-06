//
// Created by simon on 06.12.24.
//

#include "notificationService.h"

#include <ncurses.h>
#include <string>

bool showPopup(const std::string& message) {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    // Get screen size
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    // Define popup size
    int popupHeight = 7, popupWidth = 40;
    int startY = (rows - popupHeight) / 2;
    int startX = (cols - popupWidth) / 2;

    // Create popup window
    WINDOW* popup = newwin(popupHeight, popupWidth, startY, startX);
    box(popup, 0, 0);

    // Display message
    mvwprintw(popup, 2, (popupWidth - message.size()) / 2, "%s", message.c_str());
    mvwprintw(popup, 4, 10, "Continue? (y/n)");

    // Refresh the popup window
    wrefresh(popup);

    // Handle user input
    bool continueGame = false;
    while (true) {
        int ch = wgetch(popup);
        if (ch == 'y' || ch == 'Y') {
            continueGame = true;
            break;
        } else if (ch == 'n' || ch == 'N') {
            break;
        }
    }

    // Clean up
    delwin(popup);
    endwin();

    return continueGame;
}
