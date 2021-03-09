/*
** EPITECH PROJECT, 2019
** create_string.c
** File description:
** create string func
*/

#include "my.h"

char *create_string(int len)
{
    char *str = malloc(sizeof(char) * (len + 1));

    for (int i = 0; i < len; i++)
        str[i] = 0;
    return (str);
}
