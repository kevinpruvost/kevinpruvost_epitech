/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** The program entry point.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "fortytwosh.h"

static int run(shell_t *shell, char *input)
{
    command_t *command = NULL;

    if ((command = sh_newcommand(input)) == NULL)
        return -1;

    shell->status = sh_dispatch(shell, command, F_NONE);

    free(input);
    sh_destroycommand(command);

    return 0;
}

int main(int argc, char const *argv[], char const *envp[])
{
    char *input = NULL;
    shell_t *shell = NULL;

    if ((shell = sh_new(envp)) == NULL)
        return PRINT(EXIT_ERROR, "%s: %s.\n", argv[0], sh_strerror(errno));
    while (!shell->exited && sh_prompt(shell, &input) != EOF) {
        if (run(shell, input) < 0)
            return PRINT(EXIT_ERROR, "%s: %s.\n", argv[0], sh_strerror(errno));
    }

    return sh_exit(shell);
}
