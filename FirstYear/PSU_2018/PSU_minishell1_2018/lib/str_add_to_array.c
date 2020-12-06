/*
** EPITECH PROJECT, 2019
** str_add_to_array.c
** File description:
** str add to array
*/

#include "my.h"

char **str_add_to_array(char *str, char **array)
{
    char **new_array = malloc(sizeof(char *) * (my_arraylen(array) + 2));
    int n = 0;

    if (array != NULL)
        for (; array[n] != NULL; n++) {
            new_array[n] = malloc(sizeof(char) * (my_strlen(array[n]) + 1));
            new_array[n] = my_strcpy(array[n]);
        }
    new_array[n] = malloc(sizeof(char) * (my_strlen(str) + 1));
    new_array[n] = str;
    new_array[n + 1] = NULL;
    return (new_array);
}
