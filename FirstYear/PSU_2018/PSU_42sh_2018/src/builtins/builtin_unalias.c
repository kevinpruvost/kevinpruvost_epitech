/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Define a new alias.
*/

#include <string.h>
#include <stdlib.h>

#include "fortytwosh.h"

BUILTIN(unalias)
{
    for (size_t i = 1; i < command->argc; i++)
        sh_unalias(shell, command->argv[i]);

    return EXIT_SUCCESS;
}
