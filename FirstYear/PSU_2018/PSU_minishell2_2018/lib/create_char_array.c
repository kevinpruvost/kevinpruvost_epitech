/*
** EPITECH PROJECT, 2019
** create_char_array.c
** File description:
** create char array
*/

#include "my.h"

char **create_char_array(int size_v, int size_h)
{
    char **array = malloc(sizeof(char *) * (size_v + 1));

    array[size_v] = NULL;
    for (int i = 0; i < size_v; i++) {
        array[i] = malloc(sizeof(char) * (size_h + 1));
        for (int j = 0; j <= size_h; j++)
            array[i][j] = 0;
    }
    return (array);
}
