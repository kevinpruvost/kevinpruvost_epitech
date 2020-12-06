/*
** EPITECH PROJECT, 2019
** animation.c
** File description:
** animation funcs
*/

#include "my.h"

void animation_bgd2(game_s *game)
{
    get_time(game->mm_vars->sprite_bgd->time_anim, game->clock);
    if (game->mm_vars->sprite_bgd->time_anim->seconds >= 0.3) {
        game->mm_vars->sprite_bgd->rect.top += 50;
        reset_time(game->mm_vars->sprite_bgd->time_anim, game->clock);
    }
    if (game->mm_vars->sprite_bgd->rect.top >= 150)
        game->mm_vars->sprite_bgd->rect.top = 0;
    sfSprite_setTextureRect(game->mm_vars->sprite_bgd->sprite,
                            game->mm_vars->sprite_bgd->rect);
}

void animation_bgd(game_s *game)
{
    game->mm_vars->sprite_bgd->scale.x = 3;
    game->mm_vars->sprite_bgd->scale.y = 3;
    sfSprite_setScale(game->mm_vars->sprite_bgd->sprite,
    game->mm_vars->sprite_bgd->scale);
    get_time(game->mm_vars->sprite_bgd->time_move, game->clock);
    if (game->mm_vars->sprite_bgd->pos.x > 1200) {
        game->mm_vars->sprite_bgd->pos.x = -600;
    } else
        game->mm_vars->sprite_bgd->pos.x += 400 *
            game->mm_vars->sprite_bgd->time_move->seconds;
    reset_time(game->mm_vars->sprite_bgd->time_move, game->clock);
    sfSprite_setPosition(game->mm_vars->sprite_bgd->sprite,
    game->mm_vars->sprite_bgd->pos);
    animation_bgd2(game);
}
