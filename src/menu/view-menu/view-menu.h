#pragma once
#ifndef VIEW_MENU_H
#define VIEW_MENU_H

#include <ncurses.h>
#include <string.h>
#include "../../../main.h"

int init_menu(void);

void draw_border(WINDOW*);
void refresh_screen(WINDOW*, int, char*[], int);
void update_selected_option(WINDOW*, int, char*[], int);
void print_logo(WINDOW*);

#endif
