/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Locate an executable.
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "fortytwosh.h"

char *sh_whereis(shell_t *shell, const char *name)
{
    char *tok = NULL;
    char path[PATH_MAX + 1];

    if (strchr(name, '/') != NULL || sh_getenv(shell, "PATH") == NULL)
        return NULL;

    strcpy(path, sh_getenv(shell, "PATH"));

    tok = strtok(path, ":");

    while (tok != NULL) {
        char *fullpath = strconcat(tok, "/", name, NULL);

        if (access(fullpath, X_OK) == 0)
            return fullpath;

        tok = strtok(NULL, ":");
    }

    return NULL;
}
