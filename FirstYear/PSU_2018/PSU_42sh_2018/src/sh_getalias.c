/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Get an alias by its name.
*/

#include <string.h>

#include "types.h"

alias_t *sh_getalias(shell_t *shell, const char *name)
{
    node_t *node = shell->aliases->first;

    while (node != NULL) {
        alias_t *alias = node->data;

        if (strcmp(name, alias->name) == 0)
            return alias;

        node = node->next;
    }

    return NULL;
}
