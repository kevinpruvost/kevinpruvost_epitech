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

int find_s(const string_t *this, const string_t *str, size_t pos)
{
    if (this == NULL || str == NULL)
        return (-1);
    return (this->find_c(this, str->str, pos));
}

int find_c(const string_t *this, const char *str, size_t pos)
{
    size_t pos_found = pos;
    char *string;

    if (this == NULL || this->str == NULL || strlen(str) > strlen(this->str))
        return (-1);
    if (pos >= strlen(this->str))
        return (-1);
    if (str == NULL || strlen(str) == 0)
        return (-1);
    string = this->str;
    for (size_t i = 0; ++i < pos; ++string);
    for (; pos_found < strlen(this->str); ++pos_found) {
        if (my_strcmp(++string, str) == 0)
            return (pos_found);
    }
    return (-1);
}

void insert_s(string_t *this, size_t pos, const string_t *str)
{
    if (this == NULL || this->str == NULL || str == NULL || str->str == NULL)
        return;

    insert_c(this, pos, str->str);
}

void insert_c2(string_t *this, size_t pos, const char *str, char *s)
{
    size_t this_pos = 0;
    size_t s_pos = 0;

    for (; this_pos != pos; ++this_pos)
        s[s_pos++] = this->str[this_pos];
    for (size_t x = 0; x < strlen(str); ++x)
        s[s_pos++] = str[x];
    for (; this_pos < strlen(this->str); ++this_pos)
        s[s_pos++] = this->str[this_pos];
}

void insert_c(string_t *this, size_t pos, const char *str)
{
    char *s;
    size_t size;

    if (this == NULL || this->str == NULL || str == NULL)
        return;
    if (pos >= strlen(this->str)) {
        append_c(this, str);
        return;
    }
    size = strlen(this->str) + strlen(str) + 1;
    s = malloc(sizeof(char) * size);
    for (size_t i = 0; i < size; ++i)
        s[i] = 0;
    insert_c2(this, pos, str, s);
    free(this->str);
    this->str = my_strdup(s);
    free(s);
}