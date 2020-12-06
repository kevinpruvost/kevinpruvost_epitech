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

void append_s(string_t *this, const string_t *ap)
{
    if (this == NULL || ap == NULL || ap->str == NULL)
        return;

    this->append_c(this, ap->str);
}

void append_c(string_t *this, const char *ap)
{
    char *s1;
    size_t size;

    if (this == NULL || ap == NULL)
        return;
    if (this->str == NULL)
        size = strlen(ap) + 1;
    else
        size = strlen(this->str) + strlen(ap) + 1;
    s1 = malloc(sizeof(char) * size);
    (this->str != NULL) ? (strcpy(s1, this->str)) : (strcpy(s1, ""));
    strcat(s1, ap);
    if (this->str != NULL)
        free(this->str);
    this->str = malloc(sizeof(char) * size);
    strcpy(this->str, s1);
    free(s1);
}

char at(const string_t *this, size_t pos)
{
    if (this == NULL || this->str == NULL)
        return (-1);
    if (pos >= strlen(this->str))
        return (-1);
    return (this->str[pos]);
}

void clear(string_t *this)
{
    if (this == NULL)
        return;
    if (this->str == NULL) {
        this->str = malloc(sizeof(char));
        this->str[0] = 0;
    } else
        for (size_t i = 0; this->str[i] != 0; this->str[i++] = 0);
}

int size(const string_t *this)
{
    if (this == NULL || this->str == NULL)
        return (-1);
    return (strlen(this->str));
}