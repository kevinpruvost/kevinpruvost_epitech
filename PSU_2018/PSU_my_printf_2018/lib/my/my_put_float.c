/*
** EPITECH PROJECT, 2018
** my_put_float.c
** File description:
** display float
*/

#include "../../include/my.h"

void my_put_float(double number)
{
    int integer_part = (int)number;
    int decimal_part;
    double to_minus;
    double mult = 10.0;

    number -= (int)(number);
    while ((int)(number * mult) < 999999) {
        decimal_part = (int)(number * mult);
        mult *= 10;
    }
    mult /= 10;
    if ((float)(decimal_part / mult + 0.00000001) < number)
        decimal_part++;
    my_put_nbr(integer_part);
    my_putchar('.');
    my_put_nbr(decimal_part);
}

char *float_parts_to_str(int integer, int decimal, char *str)
{
    char *str_integer = my_getnbr(integer);
    char *str_decimal = my_getnbr(decimal);
    int j = 0;

    for (int i = 0; str_integer[i] != 0; i++, j++)
        str[j] = str_integer[i];
    str[j] = '.';
    j++;
    for (int i = 0; str_decimal[i] != 0; i++, j++)
        str[j] = str_decimal[i];
    str[j] = 0;
    free(str_integer);
    free(str_decimal);
    return (str);
}

char *my_get_float(double number)
{
    int integer_part = (int)number;
    int decimal_part;
    double to_minus;
    double mult = 10.0;
    char *final = malloc(sizeof(char) * 28);

    number -= (int)(number);
    while ((int)(number * mult) < 999999) {
        decimal_part = (int)(number * mult);
        mult *= 10;
    }
    mult /= 10;
    if ((float)(decimal_part / mult + 0.000001) < number)
        decimal_part++;
    final = float_parts_to_str(integer_part, decimal_part, final);
    return (final);
}
