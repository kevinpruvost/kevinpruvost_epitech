/*
** EPITECH PROJECT, 2019
** my_strcpy.c
** File description:
** str to copy
*/

#include "my.h"

char *my_strcpy(char *to_copy)
{
    char *copied = malloc(sizeof(char) * (my_strlen(to_copy) + 1));

    for (int i = 0; to_copy[i] != 0; i++) {
        copied[i] = to_copy[i];
    }
    copied[my_strlen(to_copy)] = 0;
    return (copied);
}
