/*
** EPITECH PROJECT, 2019
** animation_towers.c
** File description:
** animation towers
*/

#include "my.h"

void animation_towers(game_s *game)
{
    tower_t *towers = game->lvl_vars->towers;
    float delay = 0.2;

    for (; towers != NULL; towers = towers->next) {
        get_time(towers->props->time_anim, game->clock);
        (towers->type == DMG) ? (delay = 0.15) : (delay = 0.2);
        if (towers->props->time_anim->seconds >= delay
            && towers->firing == 1) {
            (anim_sprite(towers->props, 3) == 1) ? (towers->firing = 0) : (0);
            reset_time(towers->props->time_anim, game->clock);
        }
    }
}
