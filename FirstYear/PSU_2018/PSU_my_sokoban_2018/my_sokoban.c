/*
** EPITECH PROJECT, 2018
** my_sokoban.c
** File description:
** my_sokoban processes
*/

#include "include/my.h"
#include <curses.h>

void display_my_sokoban(char **array)
{
    int y = 0;
    int x = 0;
    int length = 0;
    int height = 0;

    clear();
    for (; array[height] != 0; height++);
    for (; array[0][length] != 0; length++);
    y = LINES/2 - (height/2);
    x = COLS/2 - (length/2);
    for (int i = 0; array[i] != 0; i++)
        mvprintw(y + i, x, "%s", array[i]);
    refresh();
}

void my_sokoban_begin(void)
{
    keypad(stdscr, true);
    curs_set(false);
    set_escdelay(1);
}

void my_sokoban_end(position *player)
{
    curs_set(true);
    endwin();
    free(player);
}

char **restart_my_sokoban(char **array, char **arrayBase, position *player)
{
    for (int i = 0; array[i] != 0; i++) {
        for (int j = 0; array[i][j] != 0; j++) {
            array[i][j] = arrayBase[i][j];
        }
    }
    player = find_player(array, player);
    return (array);
}

int my_sokoban_processes(char **array, char **arrayBase)
{
    int i = 0;
    position *player = malloc(sizeof(player));
    int win = -1;

    player = find_player(array, player);
    initscr();
    my_sokoban_begin();
    for (i = 0; i != ESC && win == -1;) {
        array = move_player(array, player, i);
        array = check_o(array, arrayBase);
        win = check_win(array, arrayBase, player);
        if (i == ' ')
            restart_my_sokoban(array, arrayBase, player);
        display_my_sokoban(array);
        i = getch();
    }
    my_sokoban_end(player);
    return (win);
}
