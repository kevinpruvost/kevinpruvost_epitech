/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include <stdlib.h>
#include <stdio.h>
#include "drawing.h"

void draw_menger(char *filename, int size, int depth)
{
    unsigned int *buffer = malloc(size * size * sizeof(*buffer));
    unsigned int **img = malloc(size * sizeof(*img));

    create_image(size, buffer, img, depth);
    create_bitmap_from_buffer(size, buffer, filename);
}

int main(int ac, char **av)
{
    char *filename;
    int size;
    int depth;

    if (ac != 4) {
        printf("menger_face file_name size level\n");
        return (84);
    }
    filename = av[1];
    size = atoi(av[2]);
    depth = atoi(av[3]);
    if (size <= 0 || depth <= 0)
        return (84);
    draw_menger(filename, size, depth);
    return (0);
}