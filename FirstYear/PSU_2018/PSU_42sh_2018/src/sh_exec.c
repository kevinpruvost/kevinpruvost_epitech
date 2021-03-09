/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Execute a command.
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "fortytwosh.h"

static int parent(shell_t *shell, command_t *command, pid_t child)
{
    return sh_await(shell, command, child);
}

static int child(shell_t *shell, command_t *cmd)
{
    char *name = cmd->name;

    if (strchr(cmd->name, '/') == NULL) {
        if ((name = sh_whereis(shell, cmd->name)) == NULL)
            return PRINT(EXIT_FAILURE, "%s: %s.\n", cmd->name, E_CMD_NOTFOUND);
    }

    if (execve(name, cmd->argv, shell->env) < 0)
        return PRINT(EXIT_FAILURE, "%s: %s.\n", cmd->name, sh_strerror(errno));

    return EXIT_SUCCESS;
}

int sh_exec(shell_t *shell, command_t *command)
{
    pid_t pid;

    switch (pid = fork()) {
        case -1:
            return -1;
        case 0:
            if (child(shell, command) == EXIT_FAILURE) {
                fflush(NULL);
                _exit(EXIT_FAILURE);

                return -1;
            }

            return 0;
        default:
            return parent(shell, command, pid);
    }
}
