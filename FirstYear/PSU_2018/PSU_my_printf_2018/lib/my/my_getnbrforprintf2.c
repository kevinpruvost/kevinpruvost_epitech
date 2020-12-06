/*
** EPITECH PROJECT, 2018
** my_getnbrforprintf2.c
** File description:
** get nbr next
*/

#include "../../include/my.h"

char *my_getchar_special(char c, int *j, char *str_special)
{
    char *except = malloc(sizeof(char) * 4);

    str_special[*j] = '\\';
    *j = *j + 1;
    if (c < 10) {
        str_special[*j] = '0';
        str_special[*j+1] = '0';
        str_special[*j+2] = c + 48;
        *j = *j + 3;
    } else {
        except = my_getnbr(c);
        for (int i = 0; except[i] != 0; i++, *j = *j + 1)
            str_special[*j] = except[i];
    }
    free(except);
    return (str_special);
}

char *my_getstr_special(char *str)
{
    char *str_special = malloc(sizeof(char) * my_strlen(str) * 2);

    for (int i = 0, j = 0; str[i] != NULL; i++) {
        if (str[i] < 32 || str[i] >= 127) {
            str_special = my_getchar_special(str[i], &j, str_special);
        } else {
            str_special[j] = str[i];
            j++;
        }
    }
    return (str_special);
}
