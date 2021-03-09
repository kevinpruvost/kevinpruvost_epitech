/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Get the latest command exit status.
*/

#include "builtins.h"

BUILTIN(status)
{
    printf("%d\n", shell->status);

    return shell->status;
}
