/*
** EPITECH PROJECT, 2018
** caseCS.c
** File description:
** treat different flags
*/

#include "include/my.h"

int minimum_field(char *str)
{
    char *number_todisplay = malloc(sizeof(char) * my_strlen(str));
    int j = 0;
    int number_display = 0;
    int stop = 0;

    for (int i = 0; str[i] != 0 && stop == 0; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            number_todisplay[j] = str[i];
            j++;
        }
        if (str[i] == '.')
            stop = 1;
    }
    if (number_todisplay[0] == '0')
        number_todisplay++;
    number_display = str_to_int(number_todisplay);
    free(number_todisplay);
    return (number_display);
}

int maximum_field(char *str)
{
    char *number_todisplay = malloc(sizeof(char) * my_strlen(str));
    int j = 0;
    int number_display = 0;
    int begin = 0;

    for (int i = 0; str[i] != 0 && begin != 2; i++) {
        if (str[i] >= '0' && str[i] <= '9' && begin == 1) {
            number_todisplay[j] = str[i];
            j++;
        }
        if ((str[i] < '0' || str[i] > '9') && begin == 1)
            begin = 2;
        if (str[i] == '.')
            begin = 1;
    }
    if (number_todisplay[0] == '0')
        number_todisplay++;
    number_display = str_to_int(number_todisplay);
    free(number_todisplay);
    return (number_display);
}

void case_c(char c, char *str)
{
    int number_display = minimum_field(str);
    int to_displaylen = maximum_field(str);

    if (str[1] == '-')
        my_putchar(c);
    for (int i = 0; i < number_display; i++)
        my_putchar(' ');
    if (str[1] != '-')
        my_putchar(c);
}

char *adapt_str(int maximum_field, char *base_str)
{
    int i = 0;
    
    for (i = 0; base_str[i+1] != 0; i++);
    for (; i > maximum_field; i--)
        base_str[i] = 0;
    return (base_str);
}

void case_s(char *to_display, char *str)
{
    int number_display = minimum_field(str);
    int to_displaylen = maximum_field(str);
    char *final_display = adapt_str(to_displaylen, to_display);

    final_display = adapt_size(final_display, to_displaylen);
    special_flags(number_display, to_displaylen - 1, str, final_display);
    free(final_display);
}
