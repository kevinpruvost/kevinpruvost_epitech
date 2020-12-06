/*
** EPITECH PROJECT, 2018
** sum_stdarg.c
** File description:
** bstrap
*/

#include <stdarg.h>
#include <stdio.h>
#include "../../include/my.h"

int sum_stdarg(int i, int nb, ...)
{
    int result = 0;
    va_list vars;
    int j = 0;

    if (i == 0) {
        va_start(vars, nb);
        for (j = 0; j < nb; j++)
            result += va_arg(vars, int);
        va_end(vars);
    } else if (i == 1){
        va_start(vars, nb);
        for (j = 0; j < nb; j++)
            result += my_strlen(va_arg(vars, char *));
        va_end(vars);
    } else {
        return (84);
    }
    return (result);
}
