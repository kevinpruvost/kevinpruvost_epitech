/*
** EPITECH PROJECT, 2019
** my_pow.c
** File description:
** my_pow
*/

#include "my.h"

int my_pow(int nb, int power)
{
    int number = nb;

    if (power == 0)
        return (1);
    if (power < 0)
        return (0);
    if (power == 1)
        return (nb);
    for (int i = 1; i < power; i++) {
        number *= nb;
    }
    return (number);
}
