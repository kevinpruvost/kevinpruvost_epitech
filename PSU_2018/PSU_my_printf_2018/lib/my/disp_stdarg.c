/*
** EPITECH PROJECT, 2018
** disp_stdarg.c
** File description:
** bstrap
*/

#include <stdarg.h>
#include <stdio.h>
#include "../../include/my.h"

int disp_stdarg(char *s, ...)
{
    va_list vars;
    int nb = my_strlen(s);
    int j;

    va_start(vars, nb);
    for (j = 0; j < nb; j++) {
        if (s[j] == 'c')
            my_putchar(va_arg(vars, int));
        if (s[j] == 's')
            my_putstr(va_arg(vars, char *));
        if (s[j] == 'i')
            my_put_nbr(va_arg(vars, int));
    }
    va_end(vars);

    return (0);
}
