/*
** EPITECH PROJECT, 2019
** check_map_finished.c
** File description:
** func that check if the map is finished
*/

#include "my.h"

int is_map_finished(game_s *game)
{
    map_t *map = game->map;
    int i = 0;

    for (i = 1; map->orders[i]->order == i; i++);
    i--;
    if (map->orders[i]->x == 4 && map->orders[i]->y == 5)
        return (1);
    return (0);
}
