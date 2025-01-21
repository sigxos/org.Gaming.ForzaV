#ifndef START_GAME_H
#define START_GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 6
#define COLS 7
#define PLAYER_PIECE 'X'
#define COMPUTER_PIECE 'O'
#define EMPTY_CELL ' '

void drawBorder(WINDOW *win);
void drawBoard(WINDOW *win, char board[ROWS][COLS], int cursorCol);
void initGame(char board[ROWS][COLS]);
int dropPiece(char board[ROWS][COLS], int col, char piece);
int checkWin(char board[ROWS][COLS], char piece);
void playGame();

#endif // START_GAME_H
