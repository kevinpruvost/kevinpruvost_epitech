/*
** EPITECH PROJECT, 2019
** draw.c
** File description:
** draw funcions for settings
*/

#include "my.h"

void draw_settings2(game_s *game)
{
    for (int i = 0; i < 10; i++) {
        sfRenderWindow_drawSprite
        (game->win, game->sett_vars->sound_bar[i]->sprite, NULL);
        sfRenderWindow_drawSprite
        (game->win, game->sett_vars->music_bar[i]->sprite, NULL);
    }
    sfRenderWindow_drawSprite(game->win,
    game->sett_vars->return_button->sprite, NULL);
    sfRenderWindow_drawSprite(game->win, game->sett_vars->cursor->sprite, NULL);
    sfRenderWindow_display(game->win);
}

void draw_settings(game_s *game)
{
    sfRenderWindow_clear(game->win, sfTransparent);
    sfRenderWindow_drawSprite(game->win,
    game->sett_vars->background->sprite, NULL);
    sfRenderWindow_drawSprite(game->win,
    game->sett_vars->music_button->sprite, NULL);
    sfRenderWindow_drawSprite(game->win,
    game->sett_vars->sound_button->sprite, NULL);
    set_alpha_sett_bars(game);
    draw_settings2(game);
}
