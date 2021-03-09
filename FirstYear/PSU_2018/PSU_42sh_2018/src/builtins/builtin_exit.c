/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Exit the shell.
*/

#include <ctype.h>
#include <stdlib.h>

#include "fortytwosh.h"

static int get_code(const char *str, int *count)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]))
            continue;

        return -1;
    }

    *count = atoi(str);

    return 0;
}

BUILTIN(exit)
{
    int status = shell->status;

    if (command->argc == 2 && get_code(command->argv[1], &status) < 0)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", command->name, E_NUMBER);

    shell->exited = true;

    return status;
}
