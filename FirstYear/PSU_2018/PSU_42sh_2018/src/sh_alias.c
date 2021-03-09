/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Add a new alias.
*/

#include "fortytwosh.h"

int sh_alias(shell_t *shell, const char *name, const char *value)
{
    alias_t *alias = NULL;

    if ((alias = sh_newalias(name, value)) == NULL)
        return -1;
    if (list_push(shell->aliases, alias) < 0)
        return -1;

    return 0;
}
