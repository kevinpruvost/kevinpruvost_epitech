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
#include <stdio.h>

string_t *substr(const string_t *this, int offset, int length)
{
    string_t * str = NULL;
    size_t pos = 0;

    if (this->str == NULL || offset < 0 || offset >= (int)strlen(this->str))
        return (str);
    str = malloc(sizeof(string_t));
    if (str == NULL)
        return (NULL);
    str->str = malloc(sizeof(char) * (length + 1));
    if (str->str == NULL)
        return (str);
    for (int i = 0; i <= length; ++i)
        str->str[i] = 0;
    for (size_t i = offset; i < strlen(this->str) && (int)i < length; ++i)
        str->str[pos++] = this->str[i];
    return (str);
}

void print(const string_t *this)
{
    if (this == NULL || this->str == NULL)
        return;
    for (size_t i = 0; this->str[i]; ++i)
        printf("%c", this->str[i]);
}