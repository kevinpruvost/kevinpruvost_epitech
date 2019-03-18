/*
** EPITECH PROJECT, 2019
** proj_damage.c
** File description:
** proj damage and destruction
*/

#include "my.h"

int identify_knight_damage(proj_t *projs, mob_t *mobs)
{
    if (projs->type == HEAVY && mobs->type == TANK) {
        return (1.25);
    } else
        return (1);
}

void proj_damage_verify2(game_s *game, proj_t *projs, mob_t *mobs)
{
    int mod_knight = 1;

    if (mobs != NULL) {
        mod_knight = identify_knight_damage(projs, mobs);
        mobs->hp -= projs->damage * mod_knight;
        (mobs->hp < 0) ? (mobs->hp = 0) : (0);
        (projs->type == DOT) ?
        (mobs->dot += projs->damage * 3.75) : (0);
        (projs->type == SLOW && mobs->slow == 0) ?
        (mobs->slow = 1,
        reset_time(mobs->time_slow, game->clock)) : (0);
    }
    if (game->lvl_vars->projs == projs) {
        game->lvl_vars->projs = projs->next;
        destroy_proj(projs, projs);
    } else
        destroy_proj(game->lvl_vars->projs, projs);
}

void proj_damage_verify(game_s *game, proj_t *projs, mob_t *mobs)
{
    if ((projs->arrived == 1 || mobs == NULL) && projs != NULL) {
        proj_damage_verify2(game, projs, mobs);
    }
}

void proj_damage(game_s *game)
{
    mob_t *mobs;
    proj_t *projs = game->lvl_vars->projs;

    for (proj_t *projs_b = projs; projs_b != NULL; projs_b = projs) {
        mobs = identify_mob(game, projs->target);
        if (projs != NULL)
            projs = projs->next;
        proj_damage_verify(game, projs_b, mobs);
    }
}
