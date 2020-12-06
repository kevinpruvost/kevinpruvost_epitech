/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include <stdio.h>
#include <stdlib.h>

void set_number(char *str, int nb)
{
    if (nb < 10)
        sprintf(str, "00%d", nb);
    else if (nb < 100)
        sprintf(str, "0%d", nb);
    else
        sprintf(str, "%d", nb);
}

char *format_string(int nb1, int nb2, int nb3)
{
    char *str = malloc(sizeof(char) * 11);
    int i = 0;
    char *str1 = malloc(sizeof(char) * 3);
    char *str2 = malloc(sizeof(char) * 3);
    char *str3 = malloc(sizeof(char) * 3);

    set_number(str1, nb1);
    set_number(str2, nb2);
    set_number(str3, nb3);
    for (i = 0; i < 3; ++i)
        str[i] = str1[i];
    str[i++] = ' ';
    for (int j = 0; j < 3; ++j)
        str[i++] = str2[j];
    str[i++] = ' ';
    for (int j = 0; j < 3; ++j)
        str[i++] = str3[j];

    return (str);
}

void menger2(int size, int x, int y)
{
    printf("%s\n", format_string(size, x, y));
}

void menger(int size, int level, int a, int c)
{
    int s = size/3;

    if (level == 0)
        return;
    if (size >= 3)
        printf("%s\n", format_string(size / 3, a, c));
    if (level < 2 || size < 3)
        return;
    a -= s;
    c -= s;
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            if (x == 1 && y == 1)
                continue;
            menger(s, (level - 1), (x*s)+(s/3) + a, (y*s) + (s/3) + c);
        }
    }
}