/*
** EPITECH PROJECT, 2018
** special_flags.c
** File description:
** special flags
*/

#include "include/my.h"

void put_final_display(char *final_display, char *str)
{
    int i = 0;
    
    for (i = 0; str[i+1] != 0; i++);
    if (str[1] == '#') {
        if (str[i] == 'x')
            my_putstr("0x");
        if (str[i] == 'X')
            my_putstr("0X");
        if (str[i] == 'o')
            my_putstr("0");
    }
    if (str[1] == ' ') {
        if (final_display[0] != '-')
            my_putchar(' ');
    }
    if (str[1] == '+') {
        if (final_display[0] != '-')
            my_putchar('+');
    }
    my_putstr(final_display);
}

void special_flags(int number_display, int to_display_len, char *str, char *final_display)
{
    if (str[1] == '-')
        put_final_display(final_display, str);
    for (int i = 0; i + 1 < number_display - to_display_len; i++) {
        if (str[1] == '0')
            my_putchar('0');
        else
            my_putchar(' ');
    }
    if (str[1] != '-')
	put_final_display(final_display, str);
}
