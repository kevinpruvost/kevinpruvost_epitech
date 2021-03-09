/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Get the current working directory.
*/

#include <stdio.h>
#include <stdlib.h>

#include "builtins.h"

BUILTIN(pwd)
{
    UNUSED(command);

    if (shell->cwd != NULL)
        puts(shell->cwd);

    return EXIT_SUCCESS;
}
