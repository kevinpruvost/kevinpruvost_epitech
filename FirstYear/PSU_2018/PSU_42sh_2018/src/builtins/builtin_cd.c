/*
** EPITECH PROJECT, 2018
** mysh
** File description:
** Change the current working directory.
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "fortytwosh.h"

static int old(shell_t *shell)
{
    char *path = NULL;

    if ((path = sh_getenv(shell, "OLDPWD")) == NULL || *path == '\0')
        return 0;
    if (sh_chdir(shell, path, F_NONE) < 0)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", path, strerror(errno));

    return EXIT_SUCCESS;
}

static int home(shell_t *shell, command_t *command)
{
    char *path = NULL;

    if ((path = sh_getenv(shell, "HOME")) == NULL || *path == '\0')
        return EXIT_SUCCESS;
    if (sh_chdir(shell, path, F_NONE) < 0)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", command->name, E_CHDIR_HOME);

    return EXIT_SUCCESS;
}

BUILTIN(cd)
{
    char *path = command->argv[1];

    if (command->argc == 1)
        return home(shell, command);
    if (strcmp("-", path) == 0)
        return old(shell);
    if (sh_chdir(shell, path, F_NONE) < 0)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", path, strerror(errno));

    return EXIT_SUCCESS;
}
