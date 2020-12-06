/*
** EPITECH PROJECT, 2019
** clear_map.c
** File description:
** clear map
*/

#include "my.h"

void clear_map(map_t *map)
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            map->map_id[i][j] = 0;
            change_map_empty(map->map_case[i][j]);
        }
    }
    for (int order = 0; order < 10 * 6; order++) {
        map->orders[order]->x = 0;
        map->orders[order]->y = 0;
        map->orders[order]->order = 0;
    }
}
