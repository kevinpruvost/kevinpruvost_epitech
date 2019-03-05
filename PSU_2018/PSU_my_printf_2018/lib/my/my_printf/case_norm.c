/*
** EPITECH PROJECT, 2018
** case_pfs2.c
** File description:
** next
*/

#include "include/my.h"

char *adapt_f2(char *adapted, int *i, char *fd, int *j)
{
    if (*i >= my_strlen(fd)) {
        adapted[*i] = '0';
    } else {
        adapted[*i] = fd[*j];
        *j = *j + 1;
    }
    return (adapted);
}

char *adapt_di2(char *str_number, char *str_test, normalize *st, int *size)
{
    if (st->var1 < *size - my_strlen(str_test))
        str_number[st->var1] = '0';
    else {
        str_number[st->var1] = str_test[st->var2];
        st->var2 = st->var2 + 1;
    }
    return (str_number);
}
