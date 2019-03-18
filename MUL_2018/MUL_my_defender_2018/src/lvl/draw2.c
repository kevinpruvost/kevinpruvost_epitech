/*
** EPITECH PROJECT, 2019
** draw2.c
** File description:
** draw 2
*/

#include "my.h"

void draw_tower_spectres(game_s *game)
{
    void *adress = game->lvl_vars->adress;

    for (int i = 0; i < 4; i++) {
        if (adress == &game->lvl_vars->player->tower_buttons[i]) {
            sfRenderWindow_drawSprite
            (game->win,
            game->lvl_vars->player->tower_spectres[i]->sprite, NULL);
        }
    }
}

void draw_buttons_up_se(game_s *game)
{
    tower_t *towers = game->lvl_vars->towers;

    for (; towers != NULL && &towers->props != game->lvl_vars->adress;
    towers = towers->next);
    if (towers != NULL) {
        sfRenderWindow_drawSprite(game->win,
        game->lvl_vars->player->upgrade_button->sprite, NULL);
        sfRenderWindow_drawSprite(game->win,
        game->lvl_vars->player->sell_button->sprite, NULL);
    }
}

void draw_next_wave(game_s *game)
{
    float sec_gap = 0;
    game_obj *next_wave = game->lvl_vars->next_wave;
    sfColor color = {255, 255, 255, 0};

    get_time(next_wave->time_anim, game->clock);
    sec_gap = next_wave->time_anim->seconds;
    (sec_gap > 2 && sec_gap <= 3) ? (sec_gap = 2) : (0);
    if (sec_gap > 3)
        sec_gap = 5.0 - next_wave->time_anim->seconds;
    color.a = 124 * sec_gap;
    sfSprite_setColor(next_wave->sprite, color);
    if (next_wave->time_anim->seconds >= 5) {
        game->lvl_vars->next_waving = 0;
        reset_time(next_wave->time_anim, game->clock);
    }
    sfRenderWindow_drawSprite(game->win, next_wave->sprite, NULL);
}

void draw_range_preview(game_s *game)
{
    tower_t *towers = game->lvl_vars->towers;
    int type = -1;

    for (int i = 0; i < 4; i++)
        (game->lvl_vars->adress ==
        &game->lvl_vars->player->tower_buttons[i]) ? (type = i) : (0);
    (type != -1) ? (towers = NULL) : (0);
    for (; towers != NULL; towers = towers->next)
        if (game->lvl_vars->adress == &towers->props) {
            type = towers->type;
            position_range_to_tower(towers, game);
        }
    (type == DMG || type == SLOW) ? (type = 0) : (type = 1);
    sfRenderWindow_drawSprite(game->win, game->range[type]->sprite, NULL);
}

void draw_lvl_ext2(game_s *game)
{
    draw_buttons_up_se(game);
    draw_tower_spectres(game);
    if (game->lvl_vars->adress != NULL)
        draw_range_preview(game);
    if (game->lvl_vars->next_waving == 1)
        draw_next_wave(game);
}
