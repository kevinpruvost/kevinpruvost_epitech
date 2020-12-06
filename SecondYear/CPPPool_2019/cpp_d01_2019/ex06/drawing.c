/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "drawing.h"
#include "bitmap.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

void initialize_image(size_t size, unsigned int *buffer, unsigned int **img)
{
    memset(buffer, 0, size * size * sizeof(*buffer));
    for (size_t i = 0; i < size; ++i)
        img[i] = buffer + i * size;
}

void menger_draw(coord_t p, unsigned int **img, int level)
{
    point_t po = {p.x, p.y};
    uint32_t c1 = 0x000000FF/level;
    uint32_t c2 = 0x000000FF/level*16*16;
    uint32_t c3 = 0x000000FF/level*16*16*16*16;

    draw_square(img, &po, p.s/3, c1+c2+c3);
}

void create_image(size_t size, unsigned int *b, unsigned int **img, int level)
{
    point_t p = {0, 0};
    coord_t po = {size/3, size/3, size};

    initialize_image(size, b, img);
    draw_square(img, &p, size, 0x00000000);

    menger(po, level, img);
}

void create_bitmap_from_buffer(size_t size, unsigned int *b, char *filename)
{
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);

    write_bmp_header(fd, size);
    write_bmp_info_header(fd, size);
    write(fd, b, size * size * sizeof(*b));
    close(fd);
}

void draw_square(uint32_t **img, const point_t *or, size_t size, uint32_t c)
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            img[or->y + i][or->x + j] = c;
        }
    }
}