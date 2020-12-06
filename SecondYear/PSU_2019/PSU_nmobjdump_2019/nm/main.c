/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** nm main
*/

#include "nm.h"

#include <string.h>

static int get_args(unsigned int ac, char **av)
{
    unsigned int i = 0;
    bool multiple = false;

    if (ac > 2)
        multiple = true;
    while (++i < ac) {
        if (nm(av[i], multiple) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int ac, char **av)
{
    if (ac == 1)
        return (nm("a.out", false));
    if (!strcmp(av[1], "--help") || !strcmp(av[1], "-h")) {
        printf("Usage: my_nm [file(s)]\n");
        return EXIT_SUCCESS;
    }
    return get_args(ac, av);
}