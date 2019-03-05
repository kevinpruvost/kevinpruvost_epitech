/*
** EPITECH PROJECT, 2018
** caseBXO.c
** File description:
** cases for binary, hexa and octal
*/

#include "include/my.h"

char *adapt_majx(char *final_display)
{
    for (int i = 0; final_display[i] != 0; i++)
        if (final_display[i] >= 'a' && final_display[i] <= 'f')
            final_display[i] -= 32;
    return (final_display);
}

char *adapt_size(char *final_display, int size)
{
    char *adapted = malloc(sizeof(char) * size);
    normalize *st = malloc(sizeof(st));

    if (my_strlen(final_display) > size) {
        for (int i = 0; i < size && final_display[i] != 0; i++)
            adapted[i] = final_display[i];
    } else if (my_strlen(final_display) < size) {
        for (st->var1 = 0, st->var2 = 0; st->var1 < size; st->var1++)
            adapted = adapt_di2(adapted, final_display, st, &size);
    }
    if (my_strlen(final_display) == size)
        for (int i = 0; final_display[i] != 0; i++)
            adapted[i] = final_display[i];
    free(st);
    return (adapted);
}

void case_x(unsigned int number, char *str, char letter)
{
    int number_display = minimum_field(str);
    int to_display_len = maximum_field(str);
    char *final_display = my_get_nbrhexa(number);

    if (str[1] == '#') {
        my_putchar('0');
        if (letter == 'X')
            my_putchar('X');
        else
            my_putchar('x');
    }
    if (letter == 'X')
        final_display = adapt_majx(final_display);
    special_flags(number_display, to_display_len, str, final_display);
    free(final_display);
}

void case_o(unsigned int number, char *str)
{
    int number_display = minimum_field(str);
    int to_display_len = maximum_field(str);
    char *final_display = my_get_nbrocta(number);

    final_display = adapt_size(final_display, to_display_len);
    special_flags(number_display, to_display_len, str, final_display);
    my_putstr(final_display);
    free(final_display);
}

void case_b(unsigned int number, char *str)
{
    int number_display = minimum_field(str);
    int to_display_len = maximum_field(str);
    char *final_display = my_get_unsigned_binary(number);

    final_display = adapt_size(final_display, to_display_len);
    special_flags(number_display, to_display_len, str, final_display);
    my_putstr(final_display);
    free(final_display);
}
