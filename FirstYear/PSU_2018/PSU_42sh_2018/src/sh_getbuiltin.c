/*
** EPITECH PROJECT, 2018
** mysh
** File description:
** Get a builtin from its name.
*/

#include <string.h>

#include "fortytwosh.h"

const builtin_t builtins[] = {
    ADD_BUILTIN(":", true, 0, 0),
    ADD_BUILTIN("alias", alias, 1, 0),
    ADD_BUILTIN("builtins", builtins, 0, 1),
    ADD_BUILTIN("bye", exit, 0, 2),
    ADD_BUILTIN("cd", cd, 0, 2),
    ADD_BUILTIN("chdir", cd, 0, 2),
    ADD_BUILTIN("echo", echo, 0, 0),
    ADD_BUILTIN("env", env, 0, 2),
    ADD_BUILTIN("exit", exit, 0, 2),
    ADD_BUILTIN("false", false, 0, 0),
    ADD_BUILTIN("logout", exit, 0, 1),
    ADD_BUILTIN("printenv", env, 0, 2),
    ADD_BUILTIN("pwd", pwd, 0, 0),
    ADD_BUILTIN("repeat", repeat, 3, 0),
    ADD_BUILTIN("setenv", setenv, 1, 3),
    ADD_BUILTIN("status", status, 1, 1),
    ADD_BUILTIN("true", true, 0, 0),
    ADD_BUILTIN("unalias", unalias, 2, 0),
    ADD_BUILTIN("unsetenv", unsetenv, 2, 0),
    ADD_BUILTIN("where", where, 2, 0),
    ADD_BUILTIN("which", which, 2, 0),
    END_BUILTIN()
};

builtin_t *sh_getbuiltin(const char *name)
{
    if (name == NULL)
        return NULL;

    for (size_t i = 0; builtins[i].name != NULL; i++) {
        if (strcmp(name, builtins[i].name) == 0)
            return (builtin_t *) &builtins[i];
    }

    return NULL;
}
