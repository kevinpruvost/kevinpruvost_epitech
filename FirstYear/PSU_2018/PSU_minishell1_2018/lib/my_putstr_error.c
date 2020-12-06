/*
** EPITECH PROJECT, 2019
** my_putstr_error.c
** File description:
** putstr for errors
*/

#include "my.h"
#include <unistd.h>

int my_putstr_error(char *str)
{
    int nb = my_strlen(str);
    int i = 0;

    write(2, str, nb);
}
