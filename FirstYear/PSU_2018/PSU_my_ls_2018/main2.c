/*
** EPITECH PROJECT, 2019
** main2.c
** File description:
** main functions complement
*/

#include "my.h"

char *options_create(void)
{
    char *options = malloc(sizeof(char) * 10);

    options[0] = 0;
    return (options);
}
