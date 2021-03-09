/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Dispatch a command.
*/

#include <stdlib.h>
#include <string.h>

#include "fortytwosh.h"

static int builtin(shell_t *shell, command_t *cmd, builtin_t *b)
{
    if (b->min_args != 0 && cmd->argc < b->min_args)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", cmd->name, E_BUILTIN_TFARGS);
    if (b->max_args != 0 && cmd->argc > b->max_args)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", cmd->name, E_BUILTIN_TMARGS);

    return b->callback(shell, cmd);
}

static int alias(shell_t *shell, command_t *cmd, alias_t *alias, size_t depth)
{
    command_t *c = NULL;

    if (depth > DEPTH_MAX)
        return PRINT(EXIT_FAILURE, "%s.\n", E_ALIAS_LOOP);
    if ((c = sh_newcommand(alias->value)) == NULL)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", cmd->name, sh_strerror(errno));
    if ((arrmerge(&c->argv, cmd->argv + 1, c->argc, cmd->argc - 1)) == NULL)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", cmd->name, sh_strerror(errno));

    c->name = c->argv[0];
    c->argc = c->argc + cmd->argc - 1;

    if (strcmp(c->name, alias->name) == 0)
        return sh_dispatch(shell, c, F_ALIAS);

    return sh_dispatch(shell, c, F_NONE);
}

int sh_dispatch(shell_t *shell, command_t *cmd, unsigned int f)
{
    alias_t *a = NULL;
    builtin_t *b = NULL;
    static size_t depth = 0;

    if ((f & F_ALIAS) == 0 && (a = sh_getalias(shell, cmd->name)) != NULL)
        return alias(shell, cmd, a, depth++);

    depth = 0;

    if ((b = sh_getbuiltin(cmd->name)) != NULL)
        return builtin(shell, cmd, b);

    return sh_exec(shell, cmd);
}
