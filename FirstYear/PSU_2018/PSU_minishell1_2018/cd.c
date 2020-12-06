/*
** EPITECH PROJECT, 2019
** cd.c
** File description:
** cd end funcs
*/

#include "my.h"

char **pwd_oldpwd(char **env, char *pwd)
{
    int n_pwd = 0;
    int n_oldpwd = 0;
    char *to_run = "setenv";
    char **args = malloc(sizeof(char *) * 4);
    char *error;

    args[0] = to_run;
    args[1] = "OLDPWD";
    args[2] = pwd;
    args[3] = NULL;
    env = setenv_func(to_run, args, env);
    args[1] = "PWD";
    error = getcwd(args[2], 255);
    env = setenv_func(to_run, args, env);
    free(args);
    return (env);
}
