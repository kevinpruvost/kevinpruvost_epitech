/*
** EPITECH PROJECT, 2019
** playable.c
** File description:
** playable
*/

#include "my.h"

int playable_map(game_s *game)
{
    map_t *map = game->map;
    int i = 0;

    for (i = 1; map->orders[i]->order == i; i++);
    i--;
    if (i == 60)
        return (0);
    return (1);
}
