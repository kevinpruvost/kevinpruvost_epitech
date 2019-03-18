/*
** EPITECH PROJECT, 2019
** upgrade_tower.c
** File description:
** upgrade tower funcs
*/

#include "my.h"

void upgrade_tower(game_s *game, tower_t *tower)
{
    lib_types_t *lib_types = game->lvl_vars->lib_types;

    if (game->lvl_vars->player->money >=
    lib_types->price_tower[tower->type]) {
        game->lvl_vars->player->money -=
        lib_types->price_tower[tower->type];
        tower->lvl += 1;
        tower->damage = lib_types->damage_tower[tower->type]
        * tower->lvl;
    }
}
