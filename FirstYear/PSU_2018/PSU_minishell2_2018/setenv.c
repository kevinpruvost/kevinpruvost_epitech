/*
** EPITECH PROJECT, 2019
** setenv.c
** File description:
** setenv funcs
*/

#include "my.h"

char **replace_env_setenv(char **env, char *str, char *arg)
{
    int p = -1;

    for (int i = 0, res = 1; env[i] != NULL && p == -1; i++, res = 1) {
        for (int j = 0; arg[j] != 0; j++) {
            if (env[i][j] != arg[j])
                res = 0;
        }
        if (res == 1)
            p = i;
    }
    env[p] = str;
    return (env);
}
