/*
** EPITECH PROJECT, 2019
** position_range.c
** File description:
** positions range spectrum
*/

#include "my.h"

void position_range_to_tower(tower_t *towers, game_s *game)
{
    game->range[0]->pos = towers->props->pos;
    game->range[1]->pos = towers->props->pos;
    sfSprite_setPosition(game->range[0]->sprite, towers->props->pos);
    sfSprite_setPosition(game->range[1]->sprite, towers->props->pos);
}
