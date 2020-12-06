/*
** EPITECH PROJECT, 2019
** mob_killed.c
** File description:
** mob killed actions
*/

#include "my.h"

void mob_killed_verify(game_s *game, mob_t *mobs)
{
    int death_id = rand() % 3;

    (death_id > 0) ? (death_id = DEATH2) : (0);
    (mobs->type == TANK) ? (death_id = DEATH1) : (0);
    if (mobs->hp <= 0) {
        if (game->lvl_vars->mobs == mobs) {
            game->lvl_vars->mobs = mobs->next;
            kill_mob(mobs, mobs);
        } else
            kill_mob(game->lvl_vars->mobs, mobs);
        game->lvl_vars->player->money += 10;
        sfMusic_play(game->sound_fx[death_id]);
    }
}

void mob_killed(game_s *game)
{
    mob_t *mobs = game->lvl_vars->mobs;

    for (mob_t *mobs_b = mobs; mobs != NULL; mobs_b = mobs) {
        if (mobs != NULL)
            mobs = mobs->next;
        mob_killed_verify(game, mobs_b);
    }
}
