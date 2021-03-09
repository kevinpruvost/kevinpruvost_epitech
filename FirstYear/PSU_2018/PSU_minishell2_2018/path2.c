/*
** EPITECH PROJECT, 2019
** path2.c
** File description:
** path env funcs
*/

#include "my.h"

int check_var(char *env, char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] != env[i])
            return (0);
    }
    return (1);
}

int env_var_exist(char **env, char *str)
{
    int ret = 0;

    for (int i = 0; env[i] != NULL && ret == 0; i++) {
        ret = check_var(env[i], str);
    }
    return (ret);
}
