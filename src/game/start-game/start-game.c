#include "start-game.h"

// Funzione per disegnare il bordo della finestra
void drawBorder(WINDOW *win) {
    int mX, mY;
    getmaxyx(win, mY, mX);

    mvwaddch(win, 0, 0, ACS_ULCORNER);
    mvwaddch(win, 0, mX - 1, ACS_URCORNER);
    mvwaddch(win, mY - 1, 0, ACS_LLCORNER);
    mvwaddch(win, mY - 1, mX - 1, ACS_LRCORNER);

    for (int i = 1; i < mX - 1; i++) {
        mvwaddch(win, 0, i, ACS_HLINE);
        mvwaddch(win, mY - 1, i, ACS_HLINE);
    }
    for (int i = 1; i < mY - 1; i++) {
        mvwaddch(win, i, 0, ACS_VLINE);
        mvwaddch(win, i, mX - 1, ACS_VLINE);
    }

    wrefresh(win);
}

// Funzione per disegnare la griglia con linee continue
void drawBoard(WINDOW *win, char board[ROWS][COLS], int cursorCol) {
    werase(win);
    drawBorder(win);  // Disegna il bordo

    int startX = 2;  // Offset per centrare orizzontalmente
    int startY = 2;  // Offset per centrare verticalmente

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mvwprintw(win, startY + i * 2, startX + j * 4, " %c ", board[i][j]);
            if (j < COLS - 1) {
                mvwaddch(win, startY + i * 2, startX + j * 4 + 3, ACS_VLINE);
            }
        }
        if (i < ROWS - 1) {
            for (int j = 0; j < COLS; j++) {
                mvwaddch(win, startY + i * 2 + 1, startX + j * 4, ACS_HLINE);
                if (j < COLS - 1) {
                    mvwaddch(win, startY + i * 2 + 1, startX + j * 4 + 3, ACS_PLUS);
                }
            }
        }
    }

    // Disegna il cursore sopra la griglia
    for (int j = 0; j < COLS; j++) {
        if (j == cursorCol) {
            mvwprintw(win, startY - 1, startX + j * 4, " v ");
        }
    }

    wrefresh(win);
}

// Inizializza il gioco
void initGame(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = EMPTY_CELL;
        }
    }
}

// Funzione per far cadere un pezzo nella colonna specificata
int dropPiece(char board[ROWS][COLS], int col, char piece) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == EMPTY_CELL) {
            board[i][col] = piece;
            return 1; // Successo
        }
    }
    return 0; // La colonna è piena
}

// Funzione per controllare se c'è una vittoria
int checkWin(char board[ROWS][COLS], char piece) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] == piece) {
                if (c + 3 < COLS && board[r][c + 1] == piece && board[r][c + 2] == piece && board[r][c + 3] == piece) {
                    return 1;
                }
                if (r + 3 < ROWS && board[r + 1][c] == piece && board[r + 2][c] == piece && board[r + 3][c] == piece) {
                    return 1;
                }
                if (r + 3 < ROWS && c + 3 < COLS && board[r + 1][c + 1] == piece && board[r + 2][c + 2] == piece && board[r + 3][c + 3] == piece) {
                    return 1;
                }
                if (r - 3 >= 0 && c + 3 < COLS && board[r - 1][c + 1] == piece && board[r - 2][c + 2] == piece && board[r - 3][c + 3] == piece) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Funzione principale di gioco
void playGame() {
    clear();
    clearenv();
    char board[ROWS][COLS];
    int cursorCol = 0;
    int currentPlayer = 1; // 1: Player, 2: Computer

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    srand(time(NULL));
    initGame(board);

    WINDOW *gameWin = newwin(ROWS * 2 + 3, COLS * 4 + 3, (LINES - (ROWS * 2 + 3)) / 2, (COLS * 4 + 3) / 2);

    if (gameWin == NULL) {
        printw("Errore nella creazione della finestra!\n");
        refresh();
        getch();
        endwin();
        return;
    }

    while (currentPlayer != -1) {
        drawBoard(gameWin, board, cursorCol);

        if (currentPlayer == 1) {
            int ch = getch();
            if (ch == KEY_LEFT) {
                cursorCol = (cursorCol > 0) ? cursorCol - 1 : COLS - 1;
            } else if (ch == KEY_RIGHT) {
                cursorCol = (cursorCol + 1) % COLS;
            } else if (ch == '\n') {
                if (dropPiece(board, cursorCol, PLAYER_PIECE)) {
                    if (checkWin(board, PLAYER_PIECE)) {
                        mvprintw(LINES - 2, 0, "Hai vinto!");
                        getch();
                        currentPlayer = -1;
                    } else {
                        currentPlayer = 2;
                    }
                }
            } else if (ch == 'q' || ch == 'Q') {
                currentPlayer = -1;
            }
        } else {
            int col = rand() % COLS;
            dropPiece(board, col, COMPUTER_PIECE);
            if (checkWin(board, COMPUTER_PIECE)) {
                mvprintw(LINES - 2, 0, "Il computer ha vinto! \n");
                getch();
                break;
            }
            currentPlayer = 1;
        }

        refresh();
    }

    delwin(gameWin);
    endwin();

    // Ritorna al menu principale
    printw("Tornando al menu principale \n");
    refresh();
    getch();
}
