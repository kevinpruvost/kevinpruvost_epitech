/*
** EPITECH PROJECT, 2019
** sell_tower.c
** File description:
** sell tower
*/

#include "my.h"

void sell_tower(game_s *game, tower_t *tower)
{
    tower_t *towers = game->lvl_vars->towers;
    lib_types_t *lib_types = game->lvl_vars->lib_types;

    game->lvl_vars->adress = NULL;
    if (towers == tower) {
        game->lvl_vars->towers = towers->next;
        game->lvl_vars->player->money +=
        lib_types->price_tower[towers->type] * tower->lvl / 2;
        destroy_tower(towers, tower);
    } else {
        for (; towers->next != tower && towers != NULL;
        towers = towers->next);
        game->lvl_vars->player->money +=
        lib_types->price_tower[tower->type] * tower->lvl / 2;
        destroy_tower(towers, tower);
    }
}
