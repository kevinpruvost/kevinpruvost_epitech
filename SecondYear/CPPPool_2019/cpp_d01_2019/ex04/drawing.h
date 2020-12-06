/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#ifndef DRAWING_H

#include <stdint.h>
#include <stddef.h>

typedef struct point_t {
    unsigned int x;
    unsigned int y;
} point_t;

void draw_square(uint32_t **img, const point_t *origin, size_t s, uint32_t c);

#endif