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

int compare_s(const string_t *this, const string_t *str)
{
    if (this == NULL && str == NULL)
        return (0);
    if (this == NULL)
        return (-1);
    if (str == NULL)
        return (1);

    return (this->compare_c(this, str->str));
}

int compare_c(const string_t *this, const char *str)
{
    if ((this == NULL || this->str == NULL) && str == NULL)
        return (0);
    if (this == NULL || this->str == NULL || strlen(this->str) == 0)
        return (-1);
    if (str == NULL || strlen(str) == 0)
        return (1);
    return (strcmp(this->str, str));
}

size_t copy(const string_t *this, char *s, size_t n, size_t pos)
{
    size_t cp = 0;

    if (this == NULL)
        return (0);
    if (this->str == NULL) {
        for (size_t i = 0; i <= n; s[i++] = 0);
        return (0);
    }
    for (int i = 0; n > 0; ++i) {
        if (pos < strlen(this->str)) {
            s[i] = this->str[pos++];
            ++cp;
        } else
            s[i] = 0;
        --n;
    }
    return (cp);
}

const char *c_str(const string_t *this)
{
    if (this == NULL)
        return (NULL);
    return (this->str);
}

int empty(const string_t *this)
{
    if (this == NULL || this->str == NULL)
        return (1);
    if (strlen(this->str) > 0)
        return (0);
    return (1);
}