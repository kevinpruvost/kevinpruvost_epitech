/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "menger.h"
#include <stdio.h>
#include <stdlib.h>

int *check_args(int ac, char **av)
{
    int * args;

    if (ac != 3)
        return (NULL);

    args = malloc(sizeof(int) * 2);

    args[0] = atoi(av[1]);
    args[1] = atoi(av[2]);

    return (args);
}

int verify_args(int arg1, int arg2)
{
    if (arg1 % 3 != 0 || arg1 < 0)
        return (84);
    if (arg2 < 0)
        return (84);
    return (0);
}

int main(int ac, char **av)
{
    int * args = check_args(ac, av);

    if (args == NULL)
        return (84);

    if (verify_args(args[0], args[1]) == 84) {
        free(args);
        return (84);
    }

    menger(args[0], args[1], args[0] / 3, args[0] / 3);

    free(args);
    return (0);
}