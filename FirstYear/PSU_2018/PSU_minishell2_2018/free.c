/*
** EPITECH PROJECT, 2019
** free.c
** File description:
** free funcs
*/

#include "my.h"

void free_path(char **path)
{
    int n_path = 0;

    for (n_path = 0; path[n_path] != NULL; n_path++);
    for (int i = n_path - 1; i >= 0; i--)
        free(path[i]);
    free(path);
}

void free_my_exec(char *to_run, char **args)
{
    int nb = 0;

    for (; args[nb] != NULL; nb++);
    for (int i = nb - 1; i >= 0; i--) {
        free(args[i]);
    }
    free(args);
}
