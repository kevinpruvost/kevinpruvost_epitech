/*
** EPITECH PROJECT, 2019
** my_putstr_input.c
** File description:
** my_putstr input
*/

#include "my.h"

void my_putstr_input(char *s)
{
    int len = my_strlen(s);

    write(0, s, len);
}
