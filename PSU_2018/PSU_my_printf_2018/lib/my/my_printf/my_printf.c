/*
** EPITECH PROJECT, 2018
** my_printf.c
** File description:
** my_printf main functions
*/

#include "include/my.h"
#include <stdarg.h>

int my_printf(char *str, ...)
{
    va_list vars;
    int j;
    char **str_sorted;
    char *ids;
    int nb = 0;

    str_sorted = sort_my_printf(str);
    for (int i = 0; str_sorted[i] != 0; i++)
        nb++;
    ids = identify_str_sorted(str_sorted, nb, ids);
    va_start(vars, nb);
    for (j = 0; j < nb; j++)
        my_flags_printf(ids[j], str_sorted[j], &vars);
    va_end(vars);
    free_parts(str_sorted);
    free(str_sorted);
    free(ids);
}
