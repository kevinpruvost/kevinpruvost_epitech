/*
** EPITECH PROJECT, 2018
** casePFS.c
** File description:
** case p f s
*/

#include "include/my.h"

void case_p(void *adress, char *str)
{
    int number_display = minimum_field(str);
    char *final_display = my_get_adress(adress);

    for (int i = 0; i < number_display - my_strlen(final_display); i++) {
        my_putchar(' ');
    }
    my_putstr(final_display);
    free(final_display);
}

char *decimal_f(char *final_display)
{
    char *part = malloc(sizeof(char) * my_strlen(final_display));
    int begin = 0;
    int j = 0;

    for (int i = 0; final_display[i] != 0; i++) {
        if (begin == 1) {
            part[j] = final_display[i];
            j++;
        }
        if (final_display[i] == '.')
            begin = 1;
    }
    part[j] = 0;
    return (part);
}

char *adapt_f(char *fd, int size)
{
    char *adapted;
    char *prt = decimal_f(fd);

    if (my_strlen(prt) > size) {
        adapted = fd;
        adapted[my_strlen(fd) + size - my_strlen(prt)] = 0;
    } else if (my_strlen(prt) < size) {
        for (int i = 0, j = 0; i < size + my_strlen(fd) - my_strlen(prt); i++) {
            adapt_f2(adapted, &i, fd, &j);
        }
    }
    if (my_strlen(prt) == size)
        adapted = fd;
    free(prt);
    return (adapted);
}

void case_f(double number, char *str)
{
    int number_display = minimum_field(str);
    int to_display_len = maximum_field(str);
    char *fd = my_get_float(number);

    fd = adapt_f(fd, to_display_len);
    for (int i = 0; i < number_display - my_strlen(fd); i++)
        my_putchar(' ');
    my_putstr(fd);
    free(fd);
}

void case_spec(char *string, char *str)
{
    int number_display = minimum_field(str);
    int to_display_len = maximum_field(str);
    char *fd = my_getstr_special(string);

    for (int i = 0; i < number_display - my_strlen(fd); i++) {
        my_putchar(' ');
    }
    my_putstr(fd);
    free(fd);
}
