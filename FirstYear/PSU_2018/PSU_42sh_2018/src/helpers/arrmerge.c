/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Merge two arrays together.
*/

#include <stdlib.h>
#include <string.h>

#include "types.h"

char **arrmerge(char ***dst, char **src, size_t len, size_t n)
{
    if (n == 0)
        return *dst;
    if ((*dst = realloc(*dst, (len + n + 1) * sizeof *dst)) == NULL)
        return NULL;

    for (size_t i = 0; i < n; i++) {
        if (((*dst)[len + i] = strdup(src[i])) == NULL)
            return NULL;

        (*dst)[len + i + 1] = NULL;
    }

    return *dst;
}
