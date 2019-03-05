/*
** EPITECH PROJECT, 2018
** caseDIU.c
** File description:
** case for decimal integer and unsigned
*/

#include "include/my.h"

char *adapt_di(int size, int number)
{
    char *str_number;
    char *str_test = my_getnbr(number);
    normalize *st = malloc(sizeof(st));

    if (my_strlen(str_test) > size)
        for (int i = 0; i < number && str_test[i] != 0; i++)
            str_number[i] = str_test[i];
    if (my_strlen(str_test) < size)
        for (st->var1 = 0, st->var2 = 0; st->var1 < size; st->var1++)
            str_number = adapt_di2(str_number, str_test, st, &size);
    if (my_strlen(str_test) == size)
        for (int i = 0; str_test[i] != 0 && str_test[i] != 0; i++)
            str_number[i] = str_test[i];
    free(st);
    return (str_number);
}

void case_di(int number, char *str)
{
    int number_display = minimum_field(str);
    int to_display_len = maximum_field(str);
    char *final_display = adapt_di(to_display_len, number);

    special_flags(number_display, to_display_len, str, final_display);
}

void case_u(int number, char *str)
{
    int number_display = minimum_field(str);
    int to_display_len = maximum_field(str);
    char *final_display;

    if (number < 0)
        number *= (-1);
    final_display = adapt_di(to_display_len, number);
    special_flags(number_display, to_display_len, str, final_display);
    free(final_display);
}
