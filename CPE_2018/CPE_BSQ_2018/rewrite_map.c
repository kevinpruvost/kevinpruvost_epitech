/*
** EPITECH PROJECT, 2018
** rewrite_map.c
** File description:
** rewrite the map
*/

#include "include/my.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

char **rewrite_map(char **map, int i, int j, int big_limit)
{
    for (int x = j; x <= j + big_limit - 1; x++) {
        for (int y = i; y <= i + big_limit - 1; y++) {
            map[x][y] = 'x';
        }
    }
    return (map);
}
