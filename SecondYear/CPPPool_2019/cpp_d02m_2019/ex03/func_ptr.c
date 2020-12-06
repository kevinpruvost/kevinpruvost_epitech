/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "func_ptr.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_normal(const char *str)
{
    printf("%s\n", str);
}

void print_reverse(const char *str)
{
    char *reved = malloc(sizeof(char) * (strlen(str) + 1));
    int j = strlen(str);

    for (int i = 0; i < strlen(str); ++i)
        reved[--j] = str[i];

    printf("%s\n", reved);
}

void print_upper(const char *str)
{
    char *reved = malloc(sizeof(char) * (strlen(str) + 1));

    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] >= 'a' && str[i] <= 'z')
            reved[i] = str[i] - 32;
        else
            reved[i] = str[i];
    }

    printf("%s\n", reved);

}

void print_42(const char *str)
{
    printf("42\n");
}

void do_action(action_t action, const char *str)
{
    void (*funcs[4])(const char *str) = {&print_normal, \
        &print_reverse, &print_upper, &print_42};

    if (str == NULL)
        return;

    funcs[action](str);
}