/*
** EPITECH PROJECT, 2019
** my_putstr_error.c
** File description:
** my_putstr for error output
*/

#include "my.h"

void my_putstr_error(char *s)
{
    int len = my_strlen(s);
    char c = '\n';

    write(2, s, len);
    write(2, &c, 1);
}
