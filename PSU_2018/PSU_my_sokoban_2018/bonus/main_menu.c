/*
** EPITECH PROJECT, 2018
** main_menu.c
** File description:
** menu principal
*/

#include "my_bonus.h"
#include "my.h"
#include <curses.h>

void main_menu_begin(void)
{
    keypad(stdscr, true);
    curs_set(false);
    start_color();
    init_pair(6, 9, 0);
    init_pair(7, 9, COLOR_WHITE);
}

void display_buttons(char *button1, char *button2, int cursor, int height)
{
    int b1 = 6;
    int b2 = 7;
    int x = 0;
    int y = 0;

    if (cursor == 0) {
        b1 = 7;
        b2 = 6;
    }
    x = COLS/2 - 5/2;
    y = LINES/2 - 1/2 + height/2 + 2;
    attron(COLOR_PAIR(b1));
    mvprintw(y, x, button1);
    attroff(COLOR_PAIR(b1));
    attron(COLOR_PAIR(b2));
    x = COLS/2 - 7/2;
    y = LINES/2 - 1/2 + height/2 + 4;
    mvprintw(y, x, button2);
    attroff(COLOR_PAIR(b2));
}

void display_main_menu(char *content, char *button1, char *button2, int cursor)
{
    int x = 0;
    int y = 0;
    int length = 107;
    int height = 20;
    int ltr = 0;

    clear();
    x = COLS/2 - (length/2);
    y = LINES/2 - (height/2);
    for (int i = 0, j = 0; content[i] != 0; i++, ltr++) {
        if (content[i] == '\n') {
            j++;
            ltr = 0;
        } else
            mvprintw(y + j, x + ltr, "%c", content[i]);
    }
    display_buttons(button1, button2, cursor, height);
}

int cursor_managing(int cursor, int i)
{
    if (i == KEY_UP)
        cursor++;
    if (i == KEY_DOWN)
        cursor--;
    if (cursor < 0)
        cursor = 1;
    if (cursor > 1)
        cursor = 0;
    return (cursor);
}

int main_menu(char *file)
{
    char *content = load_file_in_mem("bonus/text/menu_title");
    char *button1 = "JOUER";
    char *button2 = "QUITTER";
    int i = 0;
    int cursor = 0;

    initscr();
    main_menu_begin();
    for (i = 0; i != ' ';) {
        display_main_menu(content, button1, button2, cursor);
        i = getch();
        cursor = cursor_managing(cursor, i);
    }
    curs_set(true);
    free(content);
    endwin();
    if (cursor == 1)
        return (1);
    my_sokoban(file);
}
