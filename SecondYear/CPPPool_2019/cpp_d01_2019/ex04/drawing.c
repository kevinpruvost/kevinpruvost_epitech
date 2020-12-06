/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "drawing.h"

void draw_square(uint32_t **img, const point_t *or, size_t size, uint32_t c)
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            img[or->y + i][or->x + j] = c;
        }
    }
}