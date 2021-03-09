/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Prompt the user for input.
*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "fortytwosh.h"

static void prompt(shell_t *shell)
{
    char *cwd = shell->cwd;
    char *home = sh_getenv(shell, "HOME");

    if (home != NULL && strncmp(home, cwd, strlen(home)) == 0) {
        cwd = cwd + strlen(home);

        printf("%s~", COLOR_BOLD);
    }

    printf("%s%s\n", COLOR_BOLD, cwd);
    printf("%s→%s ", shell->status ? COLOR_RED : COLOR_GREEN, COLOR_RESET);
    fflush(stdout);
}

static int failed(char *line)
{
    free(line);

    return EOF;
}

ssize_t sh_prompt(shell_t *shell, char **input)
{
    size_t n = 0;
    ssize_t len = 0;
    char *line = NULL;

    if (isatty(STDIN_FILENO))
        prompt(shell);
    if ((len = getline(&line, &n, stdin)) == EOF)
        return failed(line);
    if (line[len - 1] == '\n')
        line[len - 1] = '\0';
    if (*line == '\0') {
        free(line);
        putchar('\n');

        return sh_prompt(shell, input);
    }

    *input = line;

    return len;
}
