/*
** EPITECH PROJECT, 2019
** stuck_map.c
** File description:
** verify is pos is stuck
*/

#include "my.h"

int stuck3(int **map_id, int x, int y)
{
    if (x == 0 && y == 0)
        if (map_id[x+1][y] > 0 && map_id[x][y+1] > 0)
            return (1);
    if (x == 9 && y == 5)
        if (map_id[x-1][y] > 0 && map_id[x][y-1] > 0)
            return (1);
    if (x == 0 && y == 5)
        if (map_id[x+1][y] > 0 && map_id[x][y-1] > 0)
            return (1);
    return (0);
}

int stuck2(int **map_id, int x, int y)
{
    if (stuck3(map_id, x, y) == 1)
        return (1);
    if (x == 9 && y == 0)
        if (map_id[x-1][y] > 0 && map_id[x][y+1] > 0)
            return (1);
    if (x == 0 && y > 0 && y < 5)
        if (map_id[x+1][y] > 0 && map_id[x][y+1] > 0 &&
            map_id[x][y-1] > 0)
            return (1);
    return (0);
}

int stuck4(int **map_id, int x, int y)
{
    if (y == 0 && x > 0 && x < 9)
        if (map_id[x+1][y] > 0 && map_id[x][y+1] > 0 &&
            map_id[x-1][y] > 0)
            return (1);
    if (x == 9 && y > 0 && y < 5)
        if (map_id[x-1][y] > 0 && map_id[x][y+1] > 0 &&
            map_id[x][y-1] > 0)
            return (1);
    if (y == 5 && x > 0 && x < 9)
        if (map_id[x+1][y] > 0 && map_id[x][y-1] > 0 &&
            map_id[x-1][y] > 0)
            return (1);
    return (0);
}

int stuck(int **map_id, int x, int y)
{
    if (stuck2(map_id, x, y) == 1)
        return (1);
    if (stuck4(map_id, x, y) == 1)
        return (1);
    if (x < 9 && x > 0 && y < 5 && y > 0)
        if (map_id[x+1][y] > 0 && map_id[x][y+1] > 0 &&
            map_id[x-1][y] > 0 && map_id[x][y-1] > 0)
            return (1);
    return (0);
}
