/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** The shell helpers.
*/

#ifndef FORTYTWO_HELPERS_H
#define FORTYTWO_HELPERS_H

#include "types.h"

char *strconcat(const char *a, ...);
char *arrtostr(char **array, size_t n, int separator);

char **arrmerge(char ***dst, char **src, size_t len, size_t n);

#endif
