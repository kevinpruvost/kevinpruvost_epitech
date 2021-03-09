/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Set an environment variable.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fortytwosh.h"

static int overwrite(shell_t *shell, const char *name, const char *val, int id)
{
    size_t new = strlen(name) + 2;

    if (val != NULL)
        new = new + strlen(val);
    if ((shell->env[id] = realloc(shell->env[id], new)) == NULL)
        return -1;
    if (val != NULL) {
        strcpy(shell->env[id] + strlen(name) + 1, val);

        return 0;
    }

    *(shell->env[id] + strlen(name) + 1) = '\0';

    return 0;
}

static int append(shell_t *shell, const char *name, const char *val)
{
    char *env = NULL;
    size_t new = (shell->envc + 2) * sizeof *shell->env;

    if ((shell->env = realloc(shell->env, new)) == NULL)
        return -1;
    if ((env = sh_newenv(name, val)) == NULL)
        return -1;

    shell->env[shell->envc] = env;
    shell->env[shell->envc + 1] = NULL;
    shell->envc++;

    return 0;
}

int sh_setenv(shell_t *shell, const char *name, const char *val, int over)
{
    size_t n = 0;

    if (sh_findenv(shell, name, &n) != NULL) {
        if (over)
            return overwrite(shell, name, val, n);

        return 0;
    }

    return append(shell, name, val);
}
