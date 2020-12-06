/*
** EPITECH PROJECT, 2019
** animation_mobs_tows.c
** File description:
** animation funcs for mobs and towers
*/

#include "my.h"

void animation_mobs(game_s *game)
{
    mob_t *mobs = game->lvl_vars->mobs;

    for (; mobs != NULL; mobs = mobs->next) {
        get_time(mobs->props->time_anim, game->clock);
        if (mobs->props->time_anim->seconds >= 0.2) {
            anim_sprite(mobs->props, 3);
            reset_time(mobs->props->time_anim, game->clock);
        }
    }
}
