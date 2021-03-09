/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Concat multiple strings into one.
*/

#include <stdarg.h>
#include <string.h>

#include "types.h"

char *strconcat(const char *a, ...)
{
    size_t i = 0;
    va_list list;
    char *str = NULL;
    static char concat[PATH_MAX + 1] = {'\0'};

    va_start(list, a);
    strcpy(concat, a);

    while ((str = va_arg(list, char *)) != NULL) {
        if ((i = i + strlen(str)) > PATH_MAX)
            return concat;

        strcat(concat, str);
    }

    va_end(list);

    return concat;
}
