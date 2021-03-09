/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Convert array of string to a single string.
*/

#include <string.h>
#include <stdlib.h>

#include "types.h"

char *arrtostr(char **array, size_t n, int separator)
{
    char *str = NULL;
    size_t len = 0;

    for (size_t i = 0; i < n && array[i] != NULL; i++) {
        len = len + strlen(array[i]) + 2;

        if ((str = realloc(str, len * sizeof (char))) == NULL)
            return NULL;
        if (i == 0)
            *str = '\0';

        strcat(str, array[i]);

        if (array[i + 1] != NULL)
            strcat(str, (char []) {separator, '\0'});
    }

    return str;
}
