/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void tab_to_2dtab(const int *tab, int length, int width, int ***res)
{
    int x = 0;

    if (*res == NULL) {
        *res = malloc(sizeof(int *) * (length));
        for (int i = 0; i < length; ++i) {
            (*res)[i] = malloc(sizeof(int) * (width));
        }
    }
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            (*res)[i][j] = tab[x++];
        }
    }
}