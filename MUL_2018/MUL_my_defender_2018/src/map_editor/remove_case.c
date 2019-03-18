/*
** EPITECH PROJECT, 2019
** remove_case.c
** File description:
** remove a case func
*/

#include "my.h"

void remove_case(game_s *game)
{
    map_t *map = game->map;
    int i = 1;
    int x = 0;
    int y = 0;

    for (; map->orders[i]->order == i; i++);
    i--;
    if (i != 0) {
        x = map->orders[i]->x;
        y = map->orders[i]->y;
        map->map_id[x][y] = 0;
        change_map_empty(map->map_case[x][y]);
        map->orders[i]->x = 0;
        map->orders[i]->y = 0;
        map->orders[i]->order = 0;
    }
}
