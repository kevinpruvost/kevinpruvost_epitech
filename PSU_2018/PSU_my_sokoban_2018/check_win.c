/*
** EPITECH PROJECT, 2018
** check_win.c
** File description:
** check for winning conditions
*/

#include "include/my.h"
#include <curses.h>

int check_x(char **array, int x, int y)
{
    if (array[x+1][y] == '#' && array[x][y-1] == '#')
        return (1);
    if (array[x+1][y] == '#' && array[x][y+1] == '#')
        return (1);
    if (array[x-1][y] == '#' && array[x][y-1] == '#')
        return (1);
    if (array[x-1][y] == '#' && array[x][y+1] == '#')
        return (1);
    return (-1);
}

int check_p_on_o(char **arrayBase, position *player)
{
    if (arrayBase[player->x][player->y] == 'O')
        return (-1);
    return (0);
}

int check_win(char **array, char **arrayBase, position *player)
{
    int win = -1;
    int nb_o = 0;

    for (int x = 0, y = 0; array[x] != 0 && win == (-1); y++) {
        if (array[x][y] == 'O')
            nb_o++;
        else if (array[x][y] == 'X')
            win = check_x(array, x, y);
        if (array[x][y] == 0) {
            y = 0;
            x++;
        }
    }
    if (nb_o == 0)
        win = 0;
    if (win == 0)
        win = check_p_on_o(arrayBase, player);
    return (win);
}
