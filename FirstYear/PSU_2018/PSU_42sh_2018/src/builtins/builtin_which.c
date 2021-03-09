/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** PGet command location (or what it is aliased to).
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "fortytwosh.h"

static int print(shell_t *shell, const char *name)
{
    char *path = NULL;
    alias_t *alias = NULL;

    if (sh_getbuiltin(name) != NULL)
        return printf("%s: shell built-in command.\n", name);
    if ((alias = sh_getalias(shell, name)) != NULL)
        return printf("%s:\t aliased to %s\n", alias->name, alias->value);
    if ((path = sh_whereis(shell, name)) != NULL)
        return printf("%s\n", path);

    printf("%s: %s.\n", name, E_CMD_NOTFOUND);

    return -1;
}

BUILTIN(which)
{
    bool error = false;

    for (size_t i = 1; i < command->argc; i++) {
        if (print(shell, command->argv[i]) < 0)
            error = true;
    }

    if (error)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
