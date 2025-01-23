#include "vMain.h"

/* Disegna i bordi */
void dEdges(WINDOW* menu) {
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

/* Aggiorna lo schermo */
void rScreen(WINDOW* menu, const int highlight, char* choices[], const int nC) {
    werase(menu);
    dEdges(menu);
    pLogo(menu);
    uSelectedOption(menu, highlight, choices, nC);
    wrefresh(menu);
}

/* Aggiorna l'opzione scelta */
void uSelectedOption(WINDOW* menu, const int highlight, char* choices[], const int nC) {
    int mX, mY;
    getmaxyx(menu, mY, mX);

    int maxOptionLength = 0;
    for (int i = 0; i < nC; i++) {
        int optionLength = (int)strlen(choices[i]) + 4;
        if (i == highlight) {
            optionLength += 4;
        }
        if (optionLength > maxOptionLength) {
            maxOptionLength = optionLength;
        }
    }

    int y = mY / 2 + 3;
    for (int i = 0; i < nC; i++) {
        int optionLength = (int)strlen(choices[i]) + 4;
        int x = (mX - maxOptionLength) / 2;

        if (i == highlight) {
            optionLength += 4;
        }

        for (int j = x - 2; j < x + maxOptionLength + 2; j++) {
            mvwaddch(menu, y - 1, j, ACS_HLINE);
            mvwaddch(menu, y + 1, j, ACS_HLINE);
        }

        const int textX = (mX - optionLength) / 2;
        if (i == highlight) {
            wattron(menu, A_BOLD | COLOR_PAIR(4));
            mvwprintw(menu, y, textX, ">>  %s  <<", choices[i]);
            wattroff(menu, A_BOLD | COLOR_PAIR(4));
        } else {
            mvwprintw(menu, y, textX, "  %s  ", choices[i]);
        }

        y += 3;
    }
}

/* Stampa il Logo */
void pLogo(WINDOW* menu) {
    const char* logo[] = {
        " _______  _______  ______    _______  _______    __   __ ",
        "|       ||       ||    _ |  |       ||   _   |  |  | |  |",
        "|    ___||   _   ||   | ||  |____   ||  |_|  |  |  |_|  |",
        "|   |___ |  | |  ||   |_||_  ____|  ||       |  |       |",
        "|    ___||  |_|  ||    __  || ______||       |  |       |",
        "|   |    |       ||   |  | || |_____ |   _   |   |     | ",
        "|___|    |_______||___|  |_||_______||__| |__|    |___|  ",
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

/* Esce dal Programma */
void eProgram() {
    clear(); endwin(); exit(EXIT_SUCCESS);
}

/* Inizializza Menu */
int iMenu(void) {
    int highlight = 0, selected = 0;
    char* choices[] = { "Gioca", "Istruzioni", "Esci" };
    constexpr int nC = sizeof(choices) / sizeof(char*);

    initscr(); cbreak(); noecho(); curs_set(0); start_color();

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

    rScreen(menu, highlight, choices, nC);

    while (true) {
        selected = wgetch(menu);

        switch (selected) {
        case KEY_UP:
            highlight = (highlight - 1 + nC) % nC;
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % nC;
            break;
        case 10:
            if (highlight == 0) {
                playGame();
            } else if (highlight == 1) {
                sInstructions(menu);
            } else if (highlight == 2) {
                eProgram();
            }
            break;
        default:
            break;
        }
        rScreen(menu, highlight, choices, nC);
    }
}