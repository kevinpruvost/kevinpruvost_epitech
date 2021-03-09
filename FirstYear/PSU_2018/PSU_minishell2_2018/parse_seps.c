/*
** EPITECH PROJECT, 2019
** parse_seps.c
** File description:
** parse seps
*/

#include "my.h"

int check_each_seps(char *str, int n, char *sep)
{
    char check[5];

    check[0] = 59;
    check[1] = '|';
    check[2] = '<';
    check[3] = '>';
    for (int i = 0; i < 4; i++) {
        if (str[n] == check[i] && str[n + 1] == check[i]
            && i >= 2) {
            sep[1] = str[n];
            sep[0] = str[n];
            return (2);
        } else if (str[n] == check[i]) {
            sep[0] = str[n];
            return (1);
        }
    }
    return (0);
}

void parse_seps(mini_t *w, char *str)
{
    char *sep = malloc(sizeof(char) * 3);

    for (int i = 0; i < 3; i++)
        sep[i] = 0;
    for (int i = 0; str[i] != 0; i++) {
        if (check_each_seps(str, i, sep) == 1) {
            i += (check_each_seps(str, i, sep) - 1);
            add_seps(w, sep);
            sep[0] = 0;
            sep[1] = 0;
        }
    }
    free(sep);
}
