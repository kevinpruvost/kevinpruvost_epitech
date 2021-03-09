/*
** EPITECH PROJECT, 2018
** mysh
** File description:
** Create a new shell instance.
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"
#include "fortytwosh.h"

static char **envdup(const char **env, size_t *i)
{
    char **dup = NULL;

    if ((dup = malloc(sizeof *dup)) == NULL)
        return dup;

    dup[0] = NULL;

    while (env[*i] != NULL) {
        if ((dup = realloc(dup, (*i + 2) * sizeof *dup)) == NULL)
            return NULL;
        if ((dup[*i] = strdup(env[*i])) == NULL)
            return NULL;

        dup[++(*i)] = NULL;
    }

    return dup;
}

static int envinit(shell_t *shell)
{
    char host[HOST_NAME_MAX + 1] = {'\0'};

    if (gethostname(host, HOST_NAME_MAX) < 0)
        return -1;
    if (sh_setenv(shell, "HOST", host, 1) < 0)
        return -1;

    return 0;
}

shell_t *sh_new(const char **env)
{
    shell_t *shell = NULL;

    if ((shell = malloc(sizeof *shell)) == NULL)
        return NULL;

    shell->envc = 0;
    shell->exited = false;
    shell->status = EXIT_SUCCESS;

    if ((shell->aliases = list_new()) == NULL)
        return NULL;
    if ((shell->env = envdup(env, &shell->envc)) == NULL)
        return NULL;

    sh_chdir(shell, ".", F_TRANSIENT);
    envinit(shell);

    return shell;
}
