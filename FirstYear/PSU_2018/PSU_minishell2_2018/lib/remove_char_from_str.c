/*
** EPITECH PROJECT, 2019
** remove_char_from_str.c
** File description:
** remove char from str
*/

#include "my.h"

int remove_char_from_str(char *str, int id)
{
    if (id >= my_strlen(str) || id < 0)
        return (84);
    str[id] = str[id+1];
    for (int i = id + 1; str[i] != 0; i++)
        str[i] = str[i+1];
}
