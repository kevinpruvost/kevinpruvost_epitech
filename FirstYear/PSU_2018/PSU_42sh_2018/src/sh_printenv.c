/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Print environment variables.
*/

#include "types.h"

int sh_printenv(shell_t *shell)
{
    for (size_t i = 0; shell->env[i] != NULL; i++)
        puts(shell->env[i]);

    return 0;
}
