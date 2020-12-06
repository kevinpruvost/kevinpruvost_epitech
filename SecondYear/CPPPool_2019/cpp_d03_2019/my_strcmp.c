/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "string.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int my_strcmp(const char *s1, const char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return (1);
    for (size_t i = 0; i < strlen(s1) && i < strlen(s2); ++i) {
        if (s1[i] != s2[i])
            return (1);
    }
    return (0);
}

char *my_strdup(const char *s)
{
    char *str = malloc(sizeof(char) * (strlen(s) + 1));

    for (size_t i = 0; s[i] != 0; ++i) {
        str[i] = s[i];
    }
    str[strlen(s)] = 0;
    return (str);
}