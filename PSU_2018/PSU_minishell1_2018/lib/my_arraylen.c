/*
** EPITECH PROJECT, 2019
** my_arraylen.c
** File description:
** array length
*/

#include "my.h"

int my_arraylen(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return (i);
}
