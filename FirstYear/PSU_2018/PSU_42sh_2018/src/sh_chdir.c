/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Change directory.
*/

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include "fortytwosh.h"

int sh_chdir(shell_t *shell, const char *path, unsigned int options)
{
    char old[PATH_MAX + 1];

    if (getcwd(old, PATH_MAX) == NULL || chdir(path) < 0)
        return -1;
    if ((options & F_TRANSIENT) == 0 && sh_setenv(shell, "OLDPWD", old, 1) < 0)
        return -1;
    if (getcwd(shell->cwd, PATH_MAX) == NULL)
        return -1;
    if (sh_setenv(shell, "PWD", shell->cwd, 1) < 0)
        return -1;

    return EXIT_SUCCESS;
}
