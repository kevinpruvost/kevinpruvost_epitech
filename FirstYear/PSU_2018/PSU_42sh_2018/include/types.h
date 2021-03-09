/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** The shell types definition.
*/

#ifndef FORTYTWOSH_TYPES_H
#define FORTYTWOSH_TYPES_H

#include "list.h"

#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>

#ifndef WCOREDUMP
#define COREDUMPED(x) (0)
#else
#define COREDUMPED(x) (WCOREDUMP(x))
#endif

#define UNUSED(x) ((void) x)
#define END_MSG() {0, NULL}
#define IF_NULL(x) if ((x) == NULL)
#define ADD_MSG(code, msg) {code, msg}
#define STATUS(c) ((shell->status = c))
#define PRINT(c, m, ...) (c + (printf(m, __VA_ARGS__) * 0))

typedef enum flag {
    F_NONE = 0,
    F_TRANSIENT = 1 << 0,
    F_ALIAS = 1 << 1
} flag_t;

typedef struct message {
    int code;
    const char *value;
} message_t;

typedef struct shell {
    char **env;
    list_t *aliases;
    char cwd[PATH_MAX + 1];
    int status;
    size_t envc;
    bool exited;
} shell_t;

typedef struct command {
    char **argv;
    const char *input;
    char *name;
    size_t argc;
} command_t;

typedef struct alias {
    const char *name;
    const char *value;
} alias_t;

typedef int (builtin_callback_t)(shell_t *shell, command_t *command);

typedef struct builtin {
    const char *name;
    builtin_callback_t *callback;
    size_t min_args;
    size_t max_args;
} builtin_t;

#endif
