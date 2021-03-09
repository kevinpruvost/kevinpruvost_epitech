/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Print environment variables.
*/

#include <stdio.h>
#include <stdlib.h>

#include "fortytwosh.h"

BUILTIN(env)
{
    char *env = NULL;

    if (command->argc > 1 && (env = sh_getenv(shell, command->argv[1])) == NULL)
        return EXIT_SUCCESS;
    if (env != NULL) {
        puts(env);

        return EXIT_SUCCESS;
    }

    sh_printenv(shell);

    return EXIT_SUCCESS;
}
