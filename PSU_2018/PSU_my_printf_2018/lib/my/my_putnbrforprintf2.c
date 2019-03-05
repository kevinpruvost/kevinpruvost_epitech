/*
** EPITECH PROJECT, 2018
** my_putnbrforprintf2.c
** File description:
** next
*/

#include "../../include/my.h"

void my_putstr_special(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] < 32 || str[i] >= 127)
            my_putchar_special(str[i]);
        else
            my_putchar(str[i]);
    }
}

void my_putchar_special(char c)
{
    my_putchar('\\');
    if (c < 10) {
        my_putstr("00");
        my_put_nbr(c);
    }
    else if (c < 100 && c > 9) {
        my_putchar('0');
        my_put_nbr(c);
    }
    else {
        my_put_nbr(c);
    }
}
