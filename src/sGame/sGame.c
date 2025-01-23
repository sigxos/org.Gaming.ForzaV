#include "sGame.h"

void drawBoard(WINDOW *window, char board[ROWS][COLUMNS], const int column) {
    werase(window);

    /* Inizio di x, y */
    constexpr int sX = 2;
    constexpr int sY = 2;

    /* Cornice Esterna */
    for (int i = 0; i < ROWS * 2 + 1; i++)
    {
        for (int j = 0; j < COLUMNS * 4 + 1; j++)
        {
            if (i == 0)
            {
                /* Angolo superiore sinistro */
                if (j == 0)
                {
                    mvwaddch(window, sY + i, sX + j, ACS_ULCORNER);
                }

                /* Angolo superiore destro */
                else
                {
                    if (j == COLUMNS * 4)
                    {
                        mvwaddch(window, sY + i, sX + j, ACS_URCORNER);
                    }

                    /* Linea orizzontale superiore */
                    else
                    {
                        if (j % 4 == 0)
                        {
                            mvwaddch(window, sY + i, sX + j, ACS_HLINE);
                        }
                    }
                }
            }
            else
            {
                if (i == ROWS * 2)
                {
                    /* Angolo inferiore sinistro */
                    if (j == 0)
                    {
                        mvwaddch(window, sY + i, sX + j, ACS_LLCORNER);
                    }
                    /* Angolo inferiore destro */
                    else
                    {
                        if (j == COLUMNS * 4)
                        {
                            mvwaddch(window, sY + i, sX + j, ACS_LRCORNER);
                        }
                        /* Linea orizzontale inferiore */
                        else
                        {
                            if (j % 4 == 0)
                            {
                                mvwaddch(window, sY + i, sX + j, ACS_HLINE);
                            }
                        }
                    }
                }
                else
                {
                    /* Linee verticali sui lati */
                    if (j == 0 || j == COLUMNS * 4)
                    {
                        mvwaddch(window, sY + i, sX + j, ACS_VLINE);
                    }


                    /* Linee incrociate in corrispondenza dei bordi della cella */
                    else if (j % 4 == 0)
                    {
                        mvwaddch(window, sY + i, sX + j, ACS_VLINE);
                    }
                }
            }
        }
    }


    /* Disegno del contenuto delle celle */
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            mvwprintw(window, sY + i * 2 + 1, sX + j * 4 + 1, " %c ", board[i][j]);
        }
    }

    /* Mostra il cursore in corrispondenza della colonna selezionata */
    for (int j = 0; j < COLUMNS; j++)
    {
        if (j == column)
        {
            mvwprintw(window, sY - 1, sX + j * 4, " v ");
        }
    }

    wrefresh(window);
}

void initGame(char board[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            board[i][j] = EMPTY;
        }
    }
}

int dropPiece(char board[ROWS][COLUMNS], int col, char piece) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == EMPTY) {
            board[i][col] = piece;
            return 1;
        }
    }
    return 0;
}

int checkWin(char board[ROWS][COLUMNS], char piece) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLUMNS; c++) {
            if (board[r][c] == piece) {
                if (c + 3 < COLUMNS && board[r][c + 1] == piece && board[r][c + 2] == piece && board[r][c + 3] == piece) {
                    return 1;
                }
                if (r + 3 < ROWS && board[r + 1][c] == piece && board[r + 2][c] == piece && board[r + 3][c] == piece) {
                    return 1;
                }
                if (r + 3 < ROWS && c + 3 < COLUMNS && board[r + 1][c + 1] == piece && board[r + 2][c + 2] == piece && board[r + 3][c + 3] == piece) {
                    return 1;
                }
                if (r - 3 >= 0 && c + 3 < COLUMNS && board[r - 1][c + 1] == piece && board[r - 2][c + 2] == piece && board[r - 3][c + 3] == piece) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void playGame() {
    clear();
    clearenv();

    printw("Premi '>' o '<' per giocare");
    getch();

    char board[ROWS][COLUMNS];
    int cursor = 0, player = 1;

    initscr(); cbreak(); noecho();

    keypad(stdscr, TRUE), curs_set(0);
    srand(time(nullptr));

    initGame(board);

    WINDOW *gameWin = newwin(ROWS * 2 + 3, COLUMNS * 4 + 3, (LINES - (ROWS * 2 + 3)) / 2, (COLUMNS * 4 + 3) / 2);

    if (gameWin == nullptr) {
        printw("Error \n");
        refresh(); getch(); endwin();
        return;
    }

    while (player != -1) {
        drawBoard(gameWin, board, cursor);

        if (player == 1) {
             const int selected = getch();
            if (selected == KEY_LEFT) {
                cursor = (cursor > 0) ? cursor - 1 : COLUMNS - 1;
            } else if (selected == KEY_RIGHT) {
                cursor = (cursor + 1) % COLUMNS;
            } else if (selected == '\n') {
                if (dropPiece(board, cursor, PLAYER)) {
                    if (checkWin(board, PLAYER)) {
                        mvprintw(LINES - 2, 0, "Hai vinto!");
                        getch(); clear();
                        player = -1;
                    } else {
                        player = 2;
                    }
                }
            } else if (selected == 'q' || selected == 'Q') {
                player = -1;
            }
        } else {
             const int column = rand() % COLUMNS;
            dropPiece(board, column, COMPUTER);
            if (checkWin(board, COMPUTER)) {
                mvprintw(LINES - 2, 0, "Il computer ha vinto! \n");
                getch();
                break;
            }
            player = 1;
        }

        refresh();
    }

    delwin(gameWin);
    endwin();

    refresh();
}