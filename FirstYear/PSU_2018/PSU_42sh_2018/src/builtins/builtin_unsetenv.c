/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Unset an environment variable.
*/

#include <stdlib.h>

#include "fortytwosh.h"

BUILTIN(unsetenv)
{
    for (size_t i = 1; i < command->argc; i++)
        sh_unsetenv(shell, command->argv[i]);

    return EXIT_SUCCESS;
}
