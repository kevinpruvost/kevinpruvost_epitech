/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Unset an environment variable.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fortytwosh.h"

int sh_unsetenv(shell_t *shell, const char *key)
{
    size_t n = strlen(key);

    for (size_t i = 0; shell->env[i] != NULL; i++) {
        if (strncmp(key, shell->env[i], n) == 0 && shell->env[i][n] == '=') {
            free(shell->env[i]);

            for (size_t j = i; j < shell->envc; j++)
                shell->env[j] = shell->env[j + 1];

            shell->envc--;
            shell->env[shell->envc] = NULL;
        }
    }

    return 0;
}
