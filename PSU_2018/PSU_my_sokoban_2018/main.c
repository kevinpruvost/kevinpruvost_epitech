/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** sokoban main functions
*/

#include "include/my.h"

int main(int ac, char **av)
{
    char *test = av[1];

    if (ac != 2) {
        return (84);
    }
    if (av[1][0] == '-' && av[1][1] == 'h') {
        help_option();
        return (0);
    }
    return (my_sokoban(av[1]));
}
