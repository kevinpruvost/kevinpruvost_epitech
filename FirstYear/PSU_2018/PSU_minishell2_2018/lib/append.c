/*
** EPITECH PROJECT, 2019
** append.c
** File description:
** append
*/

#include "my.h"

void append(char **arr_n, char *str_n)
{
    int la = 0;

    for (la = 0; arr_n[la] != NULL && arr_n[la][0] != 0; la++);
    arr_n[la][0] = 0;
    for (int i = 0; str_n[i] != 0; i++)
        arr_n[la][i] = str_n[i];
}
