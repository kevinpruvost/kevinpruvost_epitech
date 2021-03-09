/*
** EPITECH PROJECT, 2019
** my_arrcpy.c
** File description:
** my_arrcpy
*/

#include "my.h"

char **my_arrcpy(char **arr)
{
    char **new_arr = malloc(sizeof(char *) * (my_arraylen(arr) + 1));

    for (int i = 0; arr[i] != NULL && arr[i][0] != 0; i++) {
        new_arr[i] = malloc(sizeof(char) * (my_strlen(arr[i]) + 1));
        new_arr[i+1] = NULL;
        for (int j = 0; arr[i][j] != 0; j++) {
            new_arr[i][j] = arr[i][j];
            new_arr[i][j+1] = 0;
        }
        if (new_arr[i][0] == '"' && new_arr[i][1] == 0)
            new_arr[i][0] = 0;
    }
    return (new_arr);
}
