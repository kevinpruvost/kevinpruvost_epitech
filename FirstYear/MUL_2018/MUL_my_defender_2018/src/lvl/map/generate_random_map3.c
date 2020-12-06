/*
** EPITECH PROJECT, 2019
** generate_random_map3.c
** File description:
** generate random map 3
*/

#include "my.h"

int **map_id_replace(int **map_id)
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 6; j++)
            (map_id[i][j] == 61) ?
            (map_id[i][j] = 0) : (0);
    return (map_id);
}
