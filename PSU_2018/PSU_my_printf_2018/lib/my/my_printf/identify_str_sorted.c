/*
** EPITECH PROJECT, 2018
** identify_str_sorted.c
** File description:
** identify what type
*/

#include "include/my.h"
#include <stdarg.h>

char for_type_of_disp(char *str_toidentify)
{
    for (int i = 0; str_toidentify[i] != 0; i++)
        if (is_ltr(str_toidentify[i]) == 1)
            return (str_toidentify[i]);
}

char type_of_disp(char *str_toidentify)
{
    char to_return;

    if (str_toidentify[0] != '%')
        return ('s');
    if (str_toidentify[0] == '%' && str_toidentify[1] == '%')
        return ('%');
    if (str_toidentify[0] == '%' && str_toidentify[1] != '%') {
        to_return = for_type_of_disp(str_toidentify);
    }
}

char *identify_str_sorted(char **str_sorted, int nb, char *ids)
{
    ids = malloc(sizeof(char) * nb);
    for (int i = 0; i < nb; i++) {
        ids[i] = type_of_disp(str_sorted[i]);
    }
    return (ids);
}
