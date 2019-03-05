/*
** EPITECH PROJECT, 2018
** check_o.c
** File description:
** functions to check o covered by x or p
*/

#include "include/my.h"
#include <curses.h>

char **check_o2(char **array, int x, int y)
{
    if (array[x][y] == ' ')
        array[x][y] = 'O';
    return (array);
}

char **check_o(char **array, char **arrayBase)
{
    int x = 0;
    int y = 0;

    for (; arrayBase[x] != 0; y++) {
        if (arrayBase[x][y] == 'O')
            array = check_o2(array, x, y);
        if (arrayBase[x][y] == 0) {
            y = 0;
            x++;
        }
    }
    return (array);
}
