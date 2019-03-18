/*
** EPITECH PROJECT, 2019
** dot_behaviour.c
** File description:
** dot behaviour
*/

#include "my.h"

void dot_behaviour(game_s *game)
{
    mob_t *mobs = game->lvl_vars->mobs;
    float dot_dmg = 0;

    for (; mobs != NULL; mobs = mobs->next) {
        get_time(mobs->time_dot, game->clock);
        if (mobs->dot > 0 && mobs->time_dot->seconds >= 1) {
            dot_dmg = mobs->dot / 4.0 + 6.0;
            (dot_dmg > mobs->dot) ? (dot_dmg = mobs->dot) : (0);
            mobs->dot -= dot_dmg;
            mobs->hp -= dot_dmg;
            reset_time(mobs->time_dot, game->clock);
        }
        mod_color(mobs->health_bar->sprite, 255, 255, 255);
        if (mobs->dot > 0)
            mod_color(mobs->health_bar->sprite, 105, 0, 255);
    }
}
