/*
** EPITECH PROJECT, 2018
** sort_my_printf.c
** File description:
** functions that sort the first argument
*/

#include "include/my.h"
#include "sort_my_printf2.c"
#include <stdarg.h>

void free_parts(char **parts)
{
    int i = 0;

    for (i = 0; parts[i] != 0; i++);
    for (; i >= 0; i--) {
        free(parts[i]);
    }
}

char **malloc_parts(char **parts, char *str, int nb_parts)
{
    int longueur = 1;
    int j = 0;
    int pct = 0;

    for (int i = 0, a = i + 1; str[i] != 0; i++, a = i + 1, longueur++) {
        if (pct == 1 && (is_ltr(str[i]) == 1 || str[i] == '%') && str[a] != 0) {
            pct = 2;
            i++;
            parts[j] = malloc(sizeof(char) * (longueur + 1));
            longueur = 0, j++;
        }
        if (str[i] == '%' && pct == 0)
            parts = malloc_parts2(&j, &pct, &longueur, parts);
        if (pct == 2 && str[i] == '%')
            pct = 0;
        else if (pct == 2)
            pct = 0;
    }
    parts[j] = malloc(sizeof(char));
    return (parts);
}

char **write_parts(char **parts, char *st, int nb_parts)
{
    int pct = 0;
    int j = 0;

    for (int i = 0, le = 0; st[i] != 0; i++, le++) {
        if (pct == 1 && (is_ltr(st[i]) == 1 || st[i] == '%') && st[i+1] != 0) {
            pct = 2;
            parts[j][le] = st[i];
            write_parts2(&i, &le, &j);
        }
        if (st[i] == '%' && pct == 0)
            write_parts3(&pct, &le, &j);
        if (st[i] == '%' && pct == 0 && i == 0)
            j -= 1;
        if (pct == 2 && st[i] == '%')
            pct = 1;
        else if (pct == 2)
            pct = 0;
        parts[j][le] = st[i];
    }
    return (parts);
}

char **sort_my_printf(char *str)
{
    char **parts;
    int nb_parts = 1;
    int pct = 0;

    for (int i = 0; str[i] != 0; i++) {
        if (pct == 1 && (is_ltr(str[i]) == 1 || str[i] == '%')) {
            pct = 2;
            i++, nb_parts++;
        }
        if (str[i] == '%' && pct == 0) {
            pct = 1;
            nb_parts++;
        }
        if (pct == 2 && str[i] == '%')
            pct = 1;
        else if (pct == 2)
            pct = 0;
    }
    parts = sort_my_printf2(parts, nb_parts, str);
    return (parts);
}
