/*
** EPITECH PROJECT, 2018
** my_atoi.c
** File description:
** like my_get_nbr
*/

#include <stddef.h>

int my_getnbr(char *str)
{
    int number = 0;
    int j;
    int mult = 1;
    int negative = 0;

    if (str == NULL)
        return (0);
    if (str[0] == 0)
        return (0);
    if (str[0] == '-') {
        str++;
        negative = 1;
    }
    for (j = 0; str[j+1] != 0; j++)
        if (str[j] < '0' || str[j] > '9')
            return (0);
    for (int i = j; i >= 0; i--, mult *= 10)
        number += (str[i] - 48) * mult;
    (negative == 1) ? (number *= -1) : (0);
    return (number);
}
