/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Get a shell environment variable.
*/

#include <string.h>

#include "fortytwosh.h"

char *sh_getenv(shell_t *shell, const char *name)
{
    size_t s = strlen(name);

    if (shell->env == NULL || *name == '\0')
        return NULL;
    for (size_t i = 0; shell->env[i] != NULL; i++)
        if (strncmp(shell->env[i], name, s) == 0 && shell->env[i][s] == '=')
            return shell->env[i] + s + 1;

    return NULL;
}
