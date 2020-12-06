/*
** EPITECH PROJECT, 2019
** mob_damage.c
** File description:
** mob damage
*/

#include "my.h"

void mob_damage(game_s *game)
{
    mob_t *mobs = game->lvl_vars->mobs;
    int type;

    for (mob_t *mobs_b = mobs; mobs_b != NULL; mobs_b = mobs) {
        (mobs != NULL) ? (mobs = mobs->next) : (0);
        if (mobs_b->arrived == 1) {
            type = mobs_b->type;
            (type == TANK) ? (type = 4) : (0);
            (game->lvl_vars->mobs == mobs_b) ?
            (game->lvl_vars->mobs = mobs_b->next, kill_mob(mobs_b, mobs_b))
            : (kill_mob(game->lvl_vars->mobs, mobs_b));
            game->lvl_vars->player->hp -= 2 * type;
        }
    }
}
