/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Find binary locations.
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "fortytwosh.h"

static int print(shell_t *shell, const char *name)
{
    size_t i = 0;
    char *tok = NULL;
    char path[PATH_MAX + 1];

    if (sh_getenv(shell, "PATH") == NULL)
        return -1;

    strcpy(path, sh_getenv(shell, "PATH"));

    if ((tok = strtok(path, ":")) == NULL)
        return -1;
    for (; tok != NULL; tok = strtok(NULL, ":")) {
        char *fullpath = strconcat(tok, "/", name, NULL);

        if (access(fullpath, X_OK) == 0)
            i = i + puts(fullpath);
    }

    return i ? 0 : -1;
}

BUILTIN(where)
{
    bool error = false;
    alias_t *alias = NULL;

    for (size_t i = 1; command->argv[i] != NULL; i++) {
        if (strchr(command->argv[i], '/') != NULL) {
            printf("%s: / in command makes no sense\n", command->name);

            error = true;

            continue;
        }
        if ((alias = sh_getalias(shell, command->argv[i])) != NULL)
            printf("%s is aliased to %s\n", alias->name, alias->value);
        if (sh_getbuiltin(command->argv[i]) != NULL)
            printf("%s is a shell built-in\n", command->argv[i]);
        if (print(shell, command->argv[i]) < 0)
            error = true;
    }

    return error ? EXIT_FAILURE : EXIT_SUCCESS;
}
