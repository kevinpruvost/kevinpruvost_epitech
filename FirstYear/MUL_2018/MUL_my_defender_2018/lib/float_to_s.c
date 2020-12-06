/*
** EPITECH PROJECT, 2019
** float_to_s.c
** File description:
** float to string
*/

#include "my.h"

int my_pow(int nb, int power)
{
    int res = nb;

    for (int i = 0; i < power; i++)
        res *= nb;
    return (res);
}

char *unite_floats(int integer, int decint)
{
    char *ints = my_getnbr(integer);
    char *decs = my_getnbr(decint);
    char *intpoint = str_add(ints, ".");
    char *result = str_add(intpoint, decs);

    free(ints);
    free(decs);
    free(intpoint);
    return (result);
}

char *float_to_s(float nb)
{
    int integer = (int)(nb);
    char *result;

    result = my_getnbr(integer);
    return (result);
}
