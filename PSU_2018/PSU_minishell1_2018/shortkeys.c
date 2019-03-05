/*
** EPITECH PROJECT, 2019
** shortkeys.c
** File description:
** shortkeys paths
*/

#include "my.h"

char *replace_spaces(char *str, int n)
{
    for (int i = n + 1; str[i] != 0; i++) {
        str[i] = str[i+1];
    }
    return (str);
}

char *check_tab_space(char *str)
{
    int gmode = -1;

    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '\t') {
            str[i] = ' ';
        }
    }
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '"')
            gmode *= (-1);
        while (str[i] == ' ' && str[i+1] == ' ' && gmode == -1) {
            str = replace_spaces(str, i);
        }
    }
    return (str);
}

char *str_sk(char *str)
{
    str = check_tab_space(str);
    if (str[0] == 'l' && str[1] == 'l') {
        str++;
        str++;
        str = str_add("ls -l", str);
    }
    if (str[0] == 0)
        return (NULL);
    return (str);
}
