/*
** EPITECH PROJECT, 2018
** sort_my_printf2.c
** File description:
** next to sort_my_printf.c
*/

#include "include/my.h"
#include <stdarg.h>

char **malloc_parts2(int *j, int *pct, int *longueur, char **parts)
{
    *pct = 1;
    parts[*j] = malloc(sizeof(char) * (*longueur + 1));
    *longueur = 0;
    *j = *j + 1;
    return (parts);
}

char **sort_my_printf2(char **parts, int nb_parts, char *str)
{
    parts = malloc(sizeof(char *) * (nb_parts + 1));
    parts = malloc_parts(parts, str, nb_parts);
    parts = write_parts(parts, str, nb_parts);
    return (parts);
}

void write_parts2(int *i, int *le, int *j)
{
    *i = *i + 1;
    *le = 0;
    *j = *j + 1;
}

void write_parts3(int *pct, int *le, int *j)
{
    *pct = 1;
    *le = 0;
    *j = *j + 1;
}
