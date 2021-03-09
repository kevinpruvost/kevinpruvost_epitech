/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Find an environment variable.
*/

#include <string.h>

#include "fortytwosh.h"

char *sh_findenv(shell_t *shell, const char *name, size_t *index)
{
    size_t n = strlen(name);

    for (size_t i = 0; shell->env[i] != NULL; i++) {
        if (strncmp(name, shell->env[i], n) == 0 && shell->env[i][n] == '=')
            return shell->env[index != NULL ? *index = i : i];
    }

    return NULL;
}
