/*
** EPITECH PROJECT, 2018
** colors.c
** File description:
** color functions
*/

#include "include/my.h"
#include <curses.h>

void color_change(char c, int y, int x)
{
    if (c == 'P') {
        attron(COLOR_PAIR(1));
        mvprintw(y, x, "%c", c);
        attroff(COLOR_PAIR(1));
    }
    if (c == 'X') {
        attron(COLOR_PAIR(2));
        mvprintw(y, x, "%c", c);
        attroff(COLOR_PAIR(2));
    }
    if (c == 'O') {
        attron(COLOR_PAIR(3));
        mvprintw(y, x, "%c", c);
        attroff(COLOR_PAIR(3));
    }
    if (c == '#') {
        attron(COLOR_PAIR(4));
        mvprintw(y, x, "%c", c);
        attroff(COLOR_PAIR(4));
    }
}

void color_change2(char c, int y, int x)
{
    if (c == ' ') {
        attron(COLOR_PAIR(5));
        mvprintw(y, x, "%c", c);
        attroff(COLOR_PAIR(5));
    }
}

void init_pairs(void)
{
    int color = 4;

    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_WHITE);
    init_pair(4, color, color);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
}
