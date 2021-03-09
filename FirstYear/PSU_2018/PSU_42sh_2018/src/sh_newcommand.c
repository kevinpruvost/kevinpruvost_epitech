/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Create a new command instance.
*/

#include <stdlib.h>
#include <string.h>

#include "fortytwosh.h"

command_t *sh_newcommand(const char *input)
{
    char *str = NULL;
    command_t *c = NULL;

    if ((c = malloc(sizeof *c)) == NULL || (str = strdup(input)) == NULL)
        return NULL;
    if ((c->name = strtok(str, COMMAND_SEPARATORS)) == NULL)
        c->name = str + strspn(str, COMMAND_SEPARATORS);

    c->argv = NULL;
    c->input = str;

    for (c->argc = 0; str != NULL; str = strtok(NULL, COMMAND_SEPARATORS)) {
        IF_NULL(c->argv = realloc(c->argv, (c->argc + 2) * sizeof *c->argv))
            return NULL;

        c->argv[c->argc++] = str;
        c->argv[c->argc] = NULL;
    }

    return c;
}
