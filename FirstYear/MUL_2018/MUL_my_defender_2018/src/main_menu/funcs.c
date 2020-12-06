/*
** EPITECH PROJECT, 2019
** funcs.c
** File description:
** main_menu funcs
*/

#include "my.h"

void draw_main_menu(game_s *game)
{
    sfRenderWindow_clear(game->win, sfTransparent);
    sfRenderWindow_drawSprite(game->win,
    game->mm_vars->background->sprite, NULL);
    sfRenderWindow_drawSprite(game->win,
    game->mm_vars->sprite_bgd->sprite, NULL);
    sfRenderWindow_drawSprite(game->win,
    game->mm_vars->play_button->sprite, NULL);
    sfRenderWindow_drawSprite(game->win,
    game->mm_vars->htp_button->sprite, NULL);
    sfRenderWindow_drawSprite(game->win,
    game->mm_vars->quit_button->sprite, NULL);
    sfRenderWindow_drawSprite(game->win,
    game->mm_vars->map_editor_button->sprite, NULL);
    sfRenderWindow_drawSprite(game->win,
    game->mm_vars->settings_button->sprite, NULL);
    for (int i = 0; i < 3; i++)
        sfRenderWindow_drawText
            (game->win, game->mm_vars->ranks[i]->text, NULL);
    sfRenderWindow_drawSprite(game->win, game->mm_vars->cursor->sprite, NULL);
    sfRenderWindow_display(game->win);
}

void event_main_menu(game_s *game)
{
    static int i = 0;

    if (i == 0) {
        actualize_score(game);
        i++;
    }
    sfMusic_setVolume(game->music, game->sett_vars->music_volume);
    if (sfMusic_getStatus(game->music) != sfPlaying)
        sfMusic_play(game->music);
    events_main_menu(game);
    animation_bgd(game);
    window_check(game->win);
}
