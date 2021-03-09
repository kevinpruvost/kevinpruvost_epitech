/*
** EPITECH PROJECT, 2019
** my_strlen.c
** File description:
** my strlen
*/

#include "my.h"

int my_strlen(char *s)
{
    int i = 0;

    for (; s[i] != 0; i++);
    return (i);
}
