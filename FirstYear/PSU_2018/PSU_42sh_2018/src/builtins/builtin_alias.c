/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Define a new alias.
*/

#include <string.h>
#include <stdlib.h>

#include "fortytwosh.h"

static int aliases(shell_t *shell)
{
    node_t *node = shell->aliases->first;

    while (node != NULL) {
        alias_t *alias = node->data;

        if (strchr(alias->value, ' ') == NULL)
            printf("%s\t%s\n", alias->name, alias->value);
        else
            printf("%s\t(%s)\n", alias->name, alias->value);

        node = node->next;
    }

    return EXIT_SUCCESS;
}

BUILTIN(alias)
{
    char *v = NULL;
    alias_t *alias = NULL;

    if (command->argc == 1)
        return aliases(shell);
    if ((v = arrtostr(command->argv + 2, command->argc - 2, ' ')) == NULL)
        return EXIT_SUCCESS;
    if ((alias = sh_getalias(shell, command->argv[1])) == NULL) {
        if (sh_alias(shell, command->argv[1], v) < 0)
            return PRINT(EXIT_FAILURE, "%s.\n", sh_strerror(errno));

        return EXIT_SUCCESS;
    }

    alias->value = v;

    return EXIT_SUCCESS;
}
