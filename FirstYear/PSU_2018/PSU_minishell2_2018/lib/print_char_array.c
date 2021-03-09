/*
** EPITECH PROJECT, 2019
** print_char_array.c
** File description:
** print char array
*/

#include "my.h"

void print_char_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        my_printf("%s\n", array[i]);
    }
}
