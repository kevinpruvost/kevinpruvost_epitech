/*
** EPITECH PROJECT, 2018
** my_getnbr.c
** File description:
** Function that returns a number sent as a string.
*/

#include <stdlib.h>
#include "../include/my.h"

char *my_revstr(char *str)
{
    int n = 0;
    char stock;
    int i;

    for (i = 0; str[i] != '\0'; i++) {
    }
    for (i = i - 1; i >= n; i--) {
        stock = str[i];
        str[i] = str[n];
        str[n] = stock;
        n++;
    }
    return (str);
}

char *my_getnbr(int nbr)
{
    char *str = malloc(sizeof(char) * 14);
    int reste = 0;
    int i = 0;

    if (nbr == 0)
        return ("0");
    while (nbr != 0) {
        reste = nbr % 10;
        str[i] = reste + 48;
        nbr -= reste;
        nbr = nbr / 10;
        i++;
    }
    str[i] = 0;
    my_revstr(str);
    return (str);
}
