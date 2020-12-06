/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include <stdlib.h>
#include <stdio.h>

int process_pyramid_path(int size, const int **map, int x, int y)
{
    int result1;
    int result2;

    if (size > 0) {
        result2 = process_pyramid_path(size - 1, map, x, y + 1);
        result1 = process_pyramid_path(size - 1, map, x + 1, y + 1);
        if (result2 < result1)
            return (map[y][x] + result2);
        return (map[y][x] + result1);
    }
    return (0);
}

int pyramid_path(int size, const int **map)
{
    if (size > 1)
        return (process_pyramid_path(size, map, 0, 0));
    return (0);
}