/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#ifndef MY_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct coord_t {
    unsigned int x;
    unsigned int y;
    size_t s;
} coord_t;

void menger(coord_t p, int level, unsigned int **img);

#endif