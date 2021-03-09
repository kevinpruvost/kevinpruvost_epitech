/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Await a command.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "fortytwosh.h"

static int exited(shell_t *shell, command_t *command, pid_t status)
{
    return WEXITSTATUS(status);
}

static int signaled(shell_t *shell, command_t *command, pid_t status)
{
    printf(sh_strsignal(WTERMSIG(status)));

    if (COREDUMPED(status))
        printf(" (core dumped)");

    putchar('\n');

    return 128 + WTERMSIG(status);
}

int sh_await(shell_t *shell, command_t *command, pid_t pid)
{
    pid_t status;

    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        return exited(shell, command, status);
    if (WIFSIGNALED(status))
        return signaled(shell, command, status);

    return EXIT_SUCCESS;
}
