#pragma once

#ifndef START_GAME_H
#define START_GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 6
#define COLUMNS 7
#define PLAYER 'X'
#define COMPUTER 'O'
#define EMPTY ' '

void drawBorder(WINDOW*);
void drawBoard(WINDOW*, char [][COLUMNS], int);
void initGame(char [][COLUMNS]);
int dropPiece(char [][COLUMNS], int, char);
int checkWin(char [][COLUMNS], char);
void playGame();

#endif
