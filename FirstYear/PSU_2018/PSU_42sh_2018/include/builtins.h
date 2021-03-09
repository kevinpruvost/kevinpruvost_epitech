/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** The shell builtins.
*/

#ifndef FORTYTWOSH_BUILTINS_H
#define FORTYTWOSH_BUILTINS_H

#include "types.h"

#define END_BUILTIN() {NULL, NULL, 0, 0}
#define ADD_BUILTIN(name, f, min, max) {name, builtin_ ## f, min, max}
#define BUILTIN(name) int builtin_ ## name(shell_t *shell, command_t *command)

BUILTIN(cd);
BUILTIN(env);
BUILTIN(pwd);
BUILTIN(echo);
BUILTIN(exit);
BUILTIN(true);
BUILTIN(false);
BUILTIN(which);
BUILTIN(where);
BUILTIN(alias);
BUILTIN(repeat);
BUILTIN(setenv);
BUILTIN(status);
BUILTIN(unalias);
BUILTIN(builtins);
BUILTIN(unsetenv);

#endif
