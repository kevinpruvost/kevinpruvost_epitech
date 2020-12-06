/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "mem_ptr.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_str(const char *str1, const char *str2, char **res)
{
    int i = 0;

    if (str1 == NULL && str2 == NULL)
        return;
    if (str1 == NULL) {
        *res = str2;
        return;
    } else if (str2 == NULL) {
        *res = str1;
        return;
    }

    if (*res == NULL)
        *res = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));

    for (int j = 0; j < strlen(str1); ++j)
        (*res)[i++] = str1[j];
    for (int j = 0; j < strlen(str2); ++j)
        (*res)[i++] = str2[j];
    (*res)[i] = 0;
}

void add_str_struct(str_op_t *str_op)
{
    int i = 0;

    if (str_op->str1 == NULL) {
        str_op->res = str_op->str2;
        return;
    } else if (str_op->str2 == NULL) {
        str_op->res = str_op->str1;
        return;
    }
    if (str_op->res == NULL)
        str_op->res = malloc(sizeof(char) * (strlen(str_op->str1) \
        + strlen(str_op->str2) + 1));

    for (int j = 0; j < strlen(str_op->str1); ++j)
        str_op->res[i++] = str_op->str1[j];
    for (int j = 0; j < strlen(str_op->str2); ++j)
        str_op->res[i++] = str_op->str2[j];
    str_op->res[i] = 0;
}