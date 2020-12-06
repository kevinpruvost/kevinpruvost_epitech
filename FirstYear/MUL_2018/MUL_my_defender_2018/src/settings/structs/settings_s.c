/*
** EPITECH PROJECT, 2019
** settings_s.c
** File description:
** settings structs
*/

#include "my.h"

game_obj *create_sound_button(sfClock *clock)
{
    sfIntRect rect = {0, 0, 100, 100};
    sfVector2f pos = {150, 300};
    game_obj *sound_button;

    sound_button = create_game_obj("assets/sprites/button_sound_fx.png",
    rect, pos, clock);
    return (sound_button);
}

game_obj *create_music_button(sfClock *clock)
{
    sfIntRect rect = {0, 0, 100, 100};
    sfVector2f pos = {150, 150};
    game_obj *music_button;

    music_button = create_game_obj("assets/sprites/button_music.png",
    rect, pos, clock);
    return (music_button);
}

settings_s *create_settings_s(sfClock *clock)
{
    settings_s *sett_vars = malloc(sizeof(settings_s));
    sfIntRect bgd_rect = {0, 0, 1000, 1000};
    sfVector2f bgd_scale = {1, 1};

    sett_vars->background = create_bgd_obj("assets/bgd/sett_bgd.png",
    bgd_rect, bgd_scale);
    sett_vars->cursor = create_cursor(clock);
    sett_vars->music_button = create_music_button(clock);
    sett_vars->sound_button = create_sound_button(clock);
    sett_vars->music_bar = create_music_bar(clock);
    sett_vars->sound_bar = create_sound_bar(clock);
    sett_vars->music_volume = 20;
    sett_vars->sound_volume = 20;
    sett_vars->return_button = create_return_button_sett(clock);
    return (sett_vars);
}

void destroy_settings_s(settings_s *sett_vars)
{
    destroy_game_obj(sett_vars->cursor);
    destroy_bgd_obj(sett_vars->background);
    destroy_game_obj(sett_vars->music_button);
    destroy_game_obj(sett_vars->sound_button);
    destroy_bars(sett_vars->music_bar);
    destroy_bars(sett_vars->sound_bar);
    destroy_game_obj(sett_vars->return_button);
    free(sett_vars);
}
