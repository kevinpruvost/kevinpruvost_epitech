/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Create a new alias instance.
*/

#include <stdlib.h>
#include <string.h>

#include "fortytwosh.h"

alias_t *sh_newalias(const char *name, const char *value)
{
    alias_t *alias = NULL;

    if ((alias = malloc(sizeof *alias)) == NULL)
        return NULL;
    if ((alias->name = strdup(name)) == NULL)
        return NULL;
    if ((alias->value = strdup(value)) == NULL)
        return NULL;

    return alias;
}
