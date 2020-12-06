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

int to_int(const string_t *this)
{
    if (this == NULL || this->str == NULL)
        return (0);
    return (atoi(this->str));
}

static size_t size_of_array(char **arr)
{
    size_t size = 0;

    if (arr == NULL)
        return (0);
    for (; arr[size] != NULL; ++size);
    return (size + 1);
}

string_t **split_s(const string_t *this, char sep)
{
    char **c_array;
    string_t **s_array;
    size_t size = 0;

    c_array = split_c(this, sep);
    size = size_of_array(c_array);
    s_array = malloc(sizeof(string_t *) * (size + 1));
    for (size_t i = 0; i <= size; ++i)
        s_array[i] = NULL;
    for (size_t i = 0; c_array[i] != NULL; ++i) {
        s_array[i] = malloc(sizeof(string_t));
        string_init(s_array[i], c_array[i]);
    }
    for (int i = 0; c_array[i] != NULL; ++i)
        free(c_array[i]);
    free(c_array);
    return (s_array);
}

char **split_c2(const string_t *this, char sep, char **array)
{
    size_t arr_index = 0;
    size_t arr_str_index = 0;

    for (size_t i = 0; i < strlen(this->str); ++i) {
        if (this->str[i] != sep)
            array[arr_index][arr_str_index++] = this->str[i];
        else {
            array[arr_index][arr_str_index] = 0;
            ++arr_index;
            arr_str_index = 0;
        }
    }
    if (array[arr_index][0] != 0)
        ++arr_index;
    array[arr_index] = NULL;
    return (array);
}

char **split_c(const string_t *this, char sep)
{
    char **array;
    size_t arr_size = 1;

    if (this == NULL || this->str == NULL || strlen(this->str) == 0) {
        array = malloc(sizeof(char *) * 2);
        array[0] = malloc(sizeof(char));
        array[0][0] = 0;
        array[1] = NULL;
        return (array);
    }
    for (size_t i = 0; i < strlen(this->str); ++i)
        (this->str[i] == sep) ? (++arr_size) : (0);
    array = malloc(sizeof(char *) * (arr_size + 1));
    for (size_t i = 0; i < arr_size; ++i) {
        array[i] = malloc(sizeof(char) * (strlen(this->str) + 1));
        for (size_t j = 0; j <= strlen(this->str); ++j)
            array[i][j] = 0;
    }
    array[arr_size] = NULL;
    return (split_c2(this, sep, array));
}