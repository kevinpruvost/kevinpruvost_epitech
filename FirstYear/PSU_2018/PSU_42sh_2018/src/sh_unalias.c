/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Remove an alias.
*/

#include <stdlib.h>

#include "fortytwosh.h"

static void unalias(list_t *aliases, node_t *node)
{
    if (aliases->first == node)
        aliases->first = node->next;
    if (aliases->last == node)
        aliases->last = node->previous;
    if (node->previous != NULL)
        node->previous->next = node->next;
    if (node->next != NULL)
        node->next->previous = node->previous;

    aliases->length--;
}

int sh_unalias(shell_t *shell, const char *name)
{
    node_t *node = NULL;
    alias_t *alias = NULL;

    if ((alias = sh_getalias(shell, name)) == NULL)
        return 0;
    for (node = shell->aliases->first; node != NULL; node = node->next) {
        if (node->data != alias)
            continue;

        unalias(shell->aliases, node);
    }

    return 0;
}
