/*
** EPITECH PROJECT, 2019
** funcs.c
** File description:
** main funcs of settings
*/

#include "my.h"

void set_alpha_sett_bars2(game_s *game, float id_music, float id_sound, int i)
{
    game->sett_vars->music_bar[i]->color.a = 255;
    if (id_music - (i + 1) < 0)
        game->sett_vars->music_bar[i]->color.a = 120;
    game->sett_vars->sound_bar[i]->color.a = 255;
    if (id_sound - (i + 1) < 0)
        game->sett_vars->sound_bar[i]->color.a = 120;
    sfSprite_setColor(game->sett_vars->sound_bar[i]->sprite,
    game->sett_vars->sound_bar[i]->color);
    sfSprite_setColor(game->sett_vars->music_bar[i]->sprite,
    game->sett_vars->music_bar[i]->color);
}

void set_alpha_sett_bars(game_s *game)
{
    float id_music = game->sett_vars->music_volume / 10;
    float id_sound = game->sett_vars->sound_volume / 10;

    for (int i = 0; i < 10; i++) {
        set_alpha_sett_bars2(game, id_music, id_sound, i);
        game->sett_vars->music_button->rect.left = 0;
        if (id_music == 0)
            game->sett_vars->music_button->rect.left = 100;
        game->sett_vars->sound_button->rect.left = 0;
        if (id_sound == 0)
            game->sett_vars->sound_button->rect.left = 100;
        sfSprite_setTextureRect(game->sett_vars->sound_button->sprite,
                                game->sett_vars->sound_button->rect);
        sfSprite_setTextureRect(game->sett_vars->music_button->sprite,
                                game->sett_vars->music_button->rect);
    }
}

void event_settings(game_s *game)
{
    sfVector2i local_pos = sfMouse_getPositionRenderWindow(game->win);

    game->sett_vars->cursor->pos.x = local_pos.x;
    game->sett_vars->cursor->pos.y = local_pos.y;
    sfSprite_setPosition(game->sett_vars->cursor->sprite,
    game->sett_vars->cursor->pos);
    event_settings2(game);
    window_check(game->win);
    game->sett_vars->return_button->scale.x = 1;
    game->sett_vars->return_button->scale.y = 1;
    if (collision_cursor(game->sett_vars->cursor,
        game->sett_vars->return_button) == 1) {
        game->sett_vars->return_button->scale.x = 1.25;
        game->sett_vars->return_button->scale.y = 1.25;
    }
    sfSprite_setScale(game->sett_vars->return_button->sprite,
    game->sett_vars->return_button->scale);
}
