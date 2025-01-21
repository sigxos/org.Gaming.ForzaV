#include "view-menu.h"

void draw_border(WINDOW* menu) {
    int mX, mY;
    getmaxyx(menu, mY, mX);

    mvwaddch(menu, 0, 0, ACS_ULCORNER);
    mvwaddch(menu, 0, mX - 1, ACS_URCORNER);
    mvwaddch(menu, mY - 1, 0, ACS_LLCORNER);
    mvwaddch(menu, mY - 1, mX - 1, ACS_LRCORNER);

    for (int i = 1; i < mX - 1; i++) {
        mvwaddch(menu, 0, i, ACS_HLINE);
        mvwaddch(menu, mY - 1, i, ACS_HLINE);
    }
    for (int i = 1; i < mY - 1; i++) {
        mvwaddch(menu, i, 0, ACS_VLINE);
        mvwaddch(menu, i, mX - 1, ACS_VLINE);
    }

    wrefresh(menu);
}

void refresh_screen(WINDOW* menu, int highlight, char* choices[], int nC) {
    werase(menu);  // Clear the window content
    draw_border(menu);
    print_logo(menu);
    update_selected_option(menu, highlight, choices, nC);
    wrefresh(menu);
}

void update_selected_option(WINDOW* menu, int highlight, char* choices[], int nC) {
    int mX, mY;
    getmaxyx(menu, mY, mX);

    int maxOptionLength = 0;
    for (int i = 0; i < nC; i++) {
        int optionLength = (int)strlen(choices[i]) + 4;
        if (i == highlight) {
            optionLength += 4;  // Add extra space for ">>" and "<<"
        }
        if (optionLength > maxOptionLength) {
            maxOptionLength = optionLength;
        }
    }

    int y = mY / 2 + 3;
    for (int i = 0; i < nC; i++) {
        int optionLength = (int)strlen(choices[i]) + 4;
        int x = (mX - maxOptionLength) / 2;  // Center based on maxOptionLength

        if (i == highlight) {
            optionLength += 4;  // Add space for selected option (">>" and "<<")
        }

        // Draw the horizontal lines above and below the option, based on maxOptionLength
        for (int j = x - 2; j < x + maxOptionLength + 2; j++) {
            mvwaddch(menu, y - 1, j, ACS_HLINE);  // Line above
            mvwaddch(menu, y + 1, j, ACS_HLINE);  // Line below
        }

        // Print the option centered, even when the lines are at their maximum length
        int textX = (mX - optionLength) / 2;  // Center the text for this option
        if (i == highlight) {
            wattron(menu, A_BOLD | COLOR_PAIR(4));
            mvwprintw(menu, y, textX, ">>  %s  <<", choices[i]);  // Center the selected option
            wattroff(menu, A_BOLD | COLOR_PAIR(4));
        } else {
            mvwprintw(menu, y, textX, "  %s  ", choices[i]);  // Center the non-selected option
        }

        y += 3;  // Add space between options
    }
}

void print_logo(WINDOW* menu) {
    const char* logo[] = {
        " _______  _______  _______  _______  _______                ",
        "(  ____ \\(  ___  )(  ____ )/ ___   )(  ___  )  |\\     /|  ",
        "| (    \\/| (   ) || (    )|\\/   )  || (   ) |  | )   ( |  ",
        "| (__    | |   | || (____)|    /   )| (___) |  | |   | |    ",
        "|  __)   | |   | ||     __)   /   / |  ___  |  ( (   ) )    ",
        "| (      | |   | || (\\ (     /   /  | (   ) |   \\ \\_/ /  ",
        "| )      | (___) || ) \\ \\__ /   (_/\\| )   ( |    \\   /  ",
        "|/       (_______)|/   \\__/(_______/|/     \\|     \\_/    ",
        "                                                            "
    };

    const char* credit = "Creato da Alessio Attilio";

    int mX, mY;
    getmaxyx(menu, mY, mX);

    int logoY = 1;
    int logoHeight = 7;
    int availableSpace = mY - logoHeight - 3;

    if (availableSpace < 1) {
        logoY = 0;
    }

    int logoX = (mX - (int)strlen(logo[0])) / 2;
    wattron(menu, COLOR_PAIR(1));

    for (int i = 0; i < 7; i++) {
        mvwprintw(menu, logoY++, logoX, "%s", logo[i]);
    }

    wattroff(menu, COLOR_PAIR(1));

    int creditX = (mX - (int)strlen(credit)) / 2;
    mvwprintw(menu, logoY + 2, creditX, "%s", credit);
}

void show_instructions() {
    clear();  // Clear the screen to hide the menu
    printw("Instructions:\n");
    printw("1. Use arrow keys to navigate the menu.\n");
    printw("2. Press Enter to select an option.\n");
    printw("3. Press 'Esc' to exit.\n");
    refresh();
    getch();  // Wait for user input before returning to the menu
}

void exit_program() {
    clear();  // Clear the screen to hide the menu
    endwin();  // End ncurses mode
    exit(EXIT_SUCCESS);
}

int init_menu(void) {
    int highlight = 0, selected = 0;
    char* choices[] = { "Gioca", "Istruzioni", "Esci" };
    int nC = sizeof(choices) / sizeof(char*);

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    int mX, mY;
    getmaxyx(stdscr, mY, mX);

    WINDOW* menu = newwin(mY, mX, 0, 0);
    if (!menu) {
        endwin();
        fprintf(stderr, "Error creating menu window.\n");
        exit(EXIT_FAILURE);
    }
    keypad(menu, true);

    refresh_screen(menu, highlight, choices, nC);

    while (true) {
        selected = wgetch(menu);

        switch (selected) {
        case KEY_UP:
            highlight = (highlight - 1 + nC) % nC;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % nC;
            break;
        case 10: // Enter key
            if (highlight == 0) {
                // Chiedi il livello
                playGame();  // Passa il livello al gioco
            } else if (highlight == 1) {
                show_instructions();
            } else if (highlight == 2) {
                exit_program();
            }
            break;
        default:
            break;
        }
        refresh_screen(menu, highlight, choices, nC);
    }
}
