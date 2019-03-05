/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** bonus main
*/

#include "my_bonus.h"
#include "my.h"
#include <curses.h>

int main(int ac, char **av)
{
    int error;

    if (ac != 2)
        return (84);
    if (av[1][0] == '-' && av[1][1] == 'h') {
        help_option();
        return (0);
    }
    return (my_sokoban(av[1]));
}
