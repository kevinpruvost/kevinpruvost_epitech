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

static size_t size_of_array(const char *const *arr)
{
    size_t size = 1;

    if (arr == NULL)
        return (0);
    for (size_t ah = 0; arr[ah] != NULL; ++ah) {
        for (size_t j = 0; arr[ah][j] != 0; ++j)
            ++size;
        ++size;
    }
    return (size);
}

void join_c(string_t *this, char delim, const char *const *tab)
{
    size_t size;
    char *str;
    size_t index = 0;

    if (this == NULL || tab == NULL)
        return;
    size = size_of_array(tab);
    str = malloc(sizeof(char) * (size + 1));
    for (size_t x = 0; tab[x] != NULL; ++x) {
        for (size_t y = 0; tab[x][y] != 0; ++y)
            str[index++] = tab[x][y];
        str[index++] = delim;
    }
    str[index] = 0;
    if (this->str != NULL)
        free(this->str);
    this->str = str;
}

static size_t size_of_array_str(const string_t * const arr)
{
    size_t size = 1;

    if (arr == NULL)
        return (0);
    for (size_t ah = 0; empty(&(arr[ah])) == 0; ++ah) {
        for (size_t j = 0; (arr[ah]).str[j] != 0; ++j)
            ++size;
        ++size;
    }
    return (size);
}

void join_s(string_t *this, char delim, const string_t *const *tab)
{
    size_t size;
    char *str;
    size_t index = 0;

    if (this == NULL || tab == NULL)
        return;
    size = size_of_array_str(*tab);
    str = malloc(sizeof(char) * (size + 1));
    for (size_t x = 0; empty(&((*tab)[x])) == 0; ++x) {
        for (size_t y = 0; ((*tab)[x]).str[y] != 0; ++y)
            str[index++] = ((*tab)[x]).str[y];
        str[index++] = delim;
    }
    str[index] = 0;
    if (this->str != NULL)
        free(this->str);
    this->str = str;
}