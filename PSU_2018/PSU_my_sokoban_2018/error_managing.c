/*
** EPITECH PROJECT, 2018
** error_managing.c
** File description:
** errors managing
*/

#include "include/my.h"

void check_oxp(char c, int *nb_o, int *nb_x, int *nb_p)
{
    if (c == 'P')
        *nb_p = *nb_p + 1;
    if (c == 'O')
        *nb_o = *nb_o + 1;
    if (c == 'X')
        *nb_x = *nb_x + 1;
}

int error_managing2(char **array)
{
    int nb_o = 0;
    int nb_x = 0;
    int nb_p = 0;

    for (int i = 0; array[i] != 0; i++) {
        for (int j = 0; array[i][j] != 0; j++) {
            check_oxp(array[i][j], &nb_o, &nb_x, &nb_p);
        }
    }
    if (nb_o == 0 || nb_p == 0 || nb_x == 0)
        return (84);
    if (nb_o > nb_x || nb_o < nb_x)
        return (84);
    if (nb_p > 1)
        return (84);
    return (0);
}

int error_managing(char **array)
{
    int error = 0;

    for (int i = 0, j = 0; array[i] != 0; j++) {
        if (array[i][j] == 0 && array[i+1] != 0) {
            j = 0;
            i++;
        }
        if ((array[i][j] == 0 || array[i][j] == '\n') && array[i+1] == 0)
            break;
        if (array[i][j] == '\n' || array[i][j] == ' ' || array[i][j] == 'P')
            j = j;
        else if (array[i][j] == '#' || array[i][j] == 'X' || array[i][j] == 'O')
            j = j;
        else
            return (84);
    }
    error = error_managing2(array);
    return (error);
}
