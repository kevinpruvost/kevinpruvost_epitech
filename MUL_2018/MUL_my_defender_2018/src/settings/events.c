/*
** EPITECH PROJECT, 2019
** events for settings
** File description:
** settings events
*/

#include "my.h"

void event_soundfx(game_s *game, int i)
{
    for (int j = 0; j < 6; j++) {
        sfMusic_setVolume(game->sound_fx[j], (i + 1) * 10);
    }
}

void event_settings4(game_s *game, sfEvent event)
{
    if (collision_cursor(game->sett_vars->cursor,
        game->sett_vars->music_button) == 1
        && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft) {
        sfMusic_play(game->beep);
        game->sett_vars->music_volume = 0;
        sfMusic_setVolume(game->music, 0);
    }
    if (collision_cursor(game->sett_vars->cursor,
        game->sett_vars->sound_button) == 1
        && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft) {
        sfMusic_play(game->beep);
        game->sett_vars->sound_volume = 0;
        sfMusic_setVolume(game->beep, 0);
        event_soundfx(game, -1);
    }
}

void event_settings3(game_s *game, sfEvent event)
{
    for (int i = 0; i < 10; i++) {
        if (collision_cursor(game->sett_vars->cursor,
            game->sett_vars->music_bar[i]) == 1
            && event.type == sfEvtMouseButtonReleased &&
            event.mouseButton.button == sfMouseLeft) {
            sfMusic_play(game->beep);
            game->sett_vars->music_volume = (i + 1) * 10;
            sfMusic_setVolume(game->music, (i + 1) * 10);
        }
        if (collision_cursor(game->sett_vars->cursor,
            game->sett_vars->sound_bar[i]) == 1
            && event.type == sfEvtMouseButtonReleased &&
            event.mouseButton.button == sfMouseLeft) {
            sfMusic_play(game->beep);
            game->sett_vars->sound_volume = (i + 1) * 10;
            sfMusic_setVolume(game->beep, (i + 1) * 10);
            event_soundfx(game, i);
        }
    }
}

void event_settings2(game_s *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->win, &event)) {
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyEscape)
            change_page_back(game);
        if (collision_cursor(game->sett_vars->cursor,
            game->sett_vars->return_button) == 1 &&
            event.type == sfEvtMouseButtonReleased &&
            event.mouseButton.button == sfMouseLeft) {
            change_page_back(game);
        }
        event_settings3(game, event);
        event_settings4(game, event);
    }
}
