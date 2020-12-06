/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** nm main
*/

#include "objdump.h"

#include <string.h>

static int get_args(unsigned int ac, char **av)
{
    unsigned int i = 0;

    while (++i < ac) {
        if (objdump(av[i]) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int ac, char **av)
{
    if (ac == 1)
        return (objdump("a.out"));
    if (!strcmp(av[1], "--help") || !strcmp(av[1], "-h")) {
        printf("Usage: my_objdump [file(s)]\n");
        return EXIT_SUCCESS;
    }
    return get_args(ac, av);
}