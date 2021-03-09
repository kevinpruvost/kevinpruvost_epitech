/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Repeat a command the specified amount of times.
*/

#include <ctype.h>
#include <stdlib.h>

#include "fortytwosh.h"
#include "builtins.h"

static int get_count(const char *str, size_t *count)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]))
            continue;

        return -1;
    }

    *count = atoi(str);

    return 0;
}

BUILTIN(repeat)
{
    size_t count = 0;
    bool failed = false;

    if (get_count(command->argv[1], &count) < 0)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", command->name, E_NUMBER);

    command->argc = command->argc - 2;
    command->argv = command->argv + 2;
    command->name = *command->argv;

    for (size_t i = 0; i < count; i++) {
        if (sh_dispatch(shell, command, F_NONE) != EXIT_SUCCESS)
            failed = true;
    }

    command->argc = command->argc + 2;
    command->argv = command->argv - 2;
    command->name = *command->argv;

    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
