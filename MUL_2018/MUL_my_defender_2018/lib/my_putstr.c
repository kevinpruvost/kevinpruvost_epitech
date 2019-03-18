/*
** EPITECH PROJECT, 2018
** my_put_str.c
** File description:
** Function that dislays one-by-one, characters of a string.
*/

#include <unistd.h>
#include "../include/my.h"

int my_putstr(char *str)
{
    int nb = my_strlen(str);

    write(1, str, nb);
    return (0);
}
