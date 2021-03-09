/*
** EPITECH PROJECT, 2019
** my_putstr_error_n.c
** File description:
** my_putstr_error_n.c
*/

#include "my.h"

void my_putstr_error_n(char *s)
{
    int len = my_strlen(s);

    write(2, s, len);
}
