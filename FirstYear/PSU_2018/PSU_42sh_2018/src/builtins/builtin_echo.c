/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Print the given string.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"

BUILTIN(echo)
{
    UNUSED(shell);

    for (size_t i = 1; command->argv[i] != NULL; i++) {
        if (i == 1 && strcmp(command->argv[i], "-n") == 0)
            continue;

        printf("%s", command->argv[i]);

        if (command->argv[i + 1] != NULL)
            putchar(' ');
    }

    if (command->argc > 1 && strcmp(command->argv[1], "-n") != 0)
        putchar('\n');

    fflush(stdout);

    return EXIT_SUCCESS;
}
