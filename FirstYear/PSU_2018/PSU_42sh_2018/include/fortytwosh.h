/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** The program main header.
*/

#ifndef FORTYTWOSH_H
#define FORTYTWOSH_H

#include "config.h"
#include "types.h"
#include "helpers.h"
#include "builtins.h"

void sh_destroycommand(command_t *command);

int sh_exit(shell_t *shell);
int sh_printenv(shell_t *shell);
int sh_exec(shell_t *shell, command_t *command);
int sh_unalias(shell_t *shell, const char *name);
int sh_unsetenv(shell_t *shell, const char *key);
int sh_await(shell_t *shell, command_t *command, pid_t pid);
int sh_alias(shell_t *shell, const char *name, const char *value);
int sh_chdir(shell_t *shell, const char *path, unsigned int options);
int sh_dispatch(shell_t *shell, command_t *command, unsigned int options);
int sh_setenv(shell_t *shell, const char *name, const char *val, int over);

ssize_t sh_prompt(shell_t *shell, char **input);

char *sh_strerror(int errnum);
char *sh_strsignal(int errnum);
char *sh_getenv(shell_t *shell, const char *name);
char *sh_whereis(shell_t *shell, const char *name);
char *sh_newenv(const char *key, const char *value);
char *sh_findenv(shell_t *shell, const char *name, size_t *index);

shell_t *sh_new(const char **env);

builtin_t *sh_getbuiltin(const char *name);

command_t *sh_newcommand(const char *input);

alias_t *sh_getalias(shell_t *shell, const char *name);
alias_t *sh_newalias(const char *name, const char *value);

#endif
