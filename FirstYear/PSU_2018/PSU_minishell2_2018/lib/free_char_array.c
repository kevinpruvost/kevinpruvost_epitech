/*
** EPITECH PROJECT, 2019
** free_char_array.c
** File description:
** free char array
*/

#include "my.h"

void free_char_array(char **array)
{
    int si = 0;

    for (si = 0; array[si] != NULL; si++);
    for (int i = si; i >= 0; i--)
        free(array[i]);
    free(array);
}
