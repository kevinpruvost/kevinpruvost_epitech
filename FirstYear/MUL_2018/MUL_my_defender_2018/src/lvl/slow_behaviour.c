/*
** EPITECH PROJECT, 2019
** slow_behaviour.c
** File description:
** slow behaviour functions
*/

#include "my.h"

void slow_behaviour(game_s *game)
{
    mob_t *mobs = game->lvl_vars->mobs;

    for (; mobs != NULL; mobs = mobs->next) {
        get_time(mobs->time_slow, game->clock);
        if (mobs->slow == 1 && mobs->time_slow->seconds > 5) {
            mobs->slow = 0;
            reset_time(mobs->time_slow, game->clock);
        }
        mod_color(mobs->props->sprite, 255, 255, 255);
        if (mobs->slow == 1)
            mod_color(mobs->props->sprite, 10, 100, 255);
    }
}
