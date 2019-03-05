/*
** EPITECH PROJECT, 2018
** window.c
** File description:
** where the main functions are
*/

#include "include/my.h"
#include <stdlib.h>

int main(int ac, char **av)
{
    char *message = load_file_in_mem("txt/help_message");

    if (ac != 2 && ac != 3) {
        my_putstr(message);
        free(message);
        return (84);
    } if (ac == 2 || ac == 3) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == 0) {
            my_putstr(message);
            free(message);
            return (0);
        }
        else
            my_runner(load_file_in_mem(av[1]), av);
    } else {
        free(message);
        return (84);
    }
    free(message);
    return (0);
}
