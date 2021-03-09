/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Print all defined builtins.
*/

#include <unistd.h>
#include <stdlib.h>

#include "fortytwosh.h"

extern builtin_t builtins[];

BUILTIN(builtins)
{
    for (size_t i = 0; builtins[i].name != NULL; i++) {
        printf("%-8s", builtins[i].name);

        if ((size_t) i % COLUMNS == (COLUMNS - 1))
            putchar('\n');
        else if (builtins[i + 1].name == NULL)
            putchar ('\n');
        else
            putchar(' ');
    }

    fflush(stdout);

    return EXIT_SUCCESS;
}
