/*
** EPITECH PROJECT, 2019
** my_put_errno.c
** File description:
** my_put_errno
*/

#include "my.h"

void my_put_errno(mini_t *w)
{
    my_putstr_error(strerror(errno));
    my_putstr_error("\n");
    if (errno != 0)
        w->error = 84;
}
