/*
** EPITECH PROJECT, 2019
** special_programs2.c
** File description:
** next funcs of sp_prog
*/

#include "my.h"

char **special_programs2(char *to_run, char **args, char **env)
{
    int i = my_arraylen(args);

    if (is_str(to_run, "cd") == 1) {
        if (i < 3)
            env = cd_func(to_run, args, env);
        else
            my_putstr("cd: Too much arguments.\n");
    }
    if (is_str(to_run, "exit") == 1) {
        exit(EXIT_SUCCESS);
    }
    return (env);
}

int setenv_alpha(char **args)
{
    for (int i = 1; args[i] != NULL; i++) {
        for (int j = 0; args[i][j] != 0; j++) {
            if (args[i][j] < 32) {
                my_putstr_error("Variable name must contain"
                                "alphanumeric characters.\n");
                return (0);
            }
        }
    }
    return (1);
}
