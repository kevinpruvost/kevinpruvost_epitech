/*
** EPITECH PROJECT, 2018
** str_to_int.c
** File description:
** str to int
*/

#include "../../include/my.h"

int str_to_int(char *str)
{
    int i = 0;
    int mult = 1;
    int result = 0;

    for (i = 0; str[i+1] != 0; i++);
    for (; i >= 0; i--) {
        result += ((str[i] - 48) * mult);
        mult *= 10;
    }
    return (result);
}
