#pragma once

#ifndef VIEW_MENU_H
#define VIEW_MENU_H

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "../../main.h"

int iMenu(void);

void dEdges(WINDOW*);
void rScreen(WINDOW*, int, char*[], int);
void uSelectedOption(WINDOW*, int, char*[], int);
void pLogo(WINDOW*);

#endif
