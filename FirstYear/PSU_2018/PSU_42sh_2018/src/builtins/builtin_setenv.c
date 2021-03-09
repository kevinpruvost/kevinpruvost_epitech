/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Set an environment variable.
*/

#include <ctype.h>
#include <stdlib.h>

#include "fortytwosh.h"

BUILTIN(setenv)
{
    const char *name = command->argv[1];

    if (command->argc == 1)
        return sh_printenv(shell) < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    if (!isalpha(*name) && *name != '_')
        return PRINT(EXIT_FAILURE, "%s: %s.\n", command->name, E_ENV_SWLETTER);
    for (size_t i = 0; name[i] != '\0'; i++) {
        if (isalpha(name[i]) || isdigit(name[i]) || name[i] == '_')
            continue;

        return PRINT(EXIT_FAILURE, "%s: %s.\n", command->name, E_ENV_ALPHANUM);
    }

    if (sh_setenv(shell, name, command->argv[2], 1) < 0)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", command->name, E_ENV_UNKNOWN);

    return EXIT_SUCCESS;
}
