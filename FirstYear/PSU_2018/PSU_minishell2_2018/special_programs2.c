/*
** EPITECH PROJECT, 2019
** special_programs2.c
** File description:
** next funcs of sp_prog
*/

#include "my.h"

void special_programs2(char *to_run, char **args, mini_t *w)
{
    int i = my_arraylen(args);

    if (my_strcmp(to_run, "cd") == 1) {
        if (i < 3)
            cd_func(to_run, args, w);
        else
            my_putstr_error("cd: Too much arguments.\n");
    }
    if (my_strcmp(to_run, "exit") == 1) {
        exit(EXIT_SUCCESS);
    }
}

int setenv_alpha(char **args)
{
    for (int i = 1; args[i] != NULL; i++) {
        for (int j = 0; args[i][j] != 0; j++) {
            if (args[i][j] < 32 || args[i][j] > 127) {
                my_putstr_error("Variable name must contain"
                                " alphanumeric characters.\n");
                return (0);
            }
        }
    }
    return (1);
}
