/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Exit the shell.
*/

#include <stdlib.h>

#include "types.h"

static void destroy(shell_t *shell)
{
    node_t *node = shell->aliases->first;

    for (size_t i = 0; shell->env[i] != NULL; i++)
        free(shell->env[i]);

    while (node != NULL) {
        free(node->data);

        node = node->next;
    }

    free(shell->env);
    list_destroy(shell->aliases);
    free(shell);
}

int sh_exit(shell_t *shell)
{
    int status = shell->status;

    destroy(shell);

    return status;
}
