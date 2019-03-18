/*
** EPITECH PROJECT, 2019
** events.c
** File description:
** events funcs for lvl
*/

#include "my.h"

void events_buttons_scale(game_s *game, sfEvent event, int i)
{
    mod_scale(game->lvl_vars->player->tower_buttons[i]->sprite, 0.75);
    set_invisible(game->lvl_vars->player->tower_descs[i]->sprite);
    if (collision_cursor(game->lvl_vars->cursor,
        game->lvl_vars->player->tower_buttons[i]) == 1) {
        mod_scale(game->lvl_vars->player->tower_buttons[i]->sprite, 1);
        set_visible(game->lvl_vars->player->tower_descs[i]->sprite);
    }
    if (is_left_click(event, game->lvl_vars->cursor,
        game->lvl_vars->player->tower_buttons[i]) == 1) {
        game->lvl_vars->adress = &game->lvl_vars->player->tower_buttons[i];
        sfMusic_play(game->beep);
    }
    if (game->lvl_vars->adress == &game->lvl_vars->player->tower_buttons[i])
        mod_scale(game->lvl_vars->player->tower_buttons[i]->sprite, 1);
}

void events_keyboard2(game_s *game, sfEvent event)
{
    player_t *player = game->lvl_vars->player;

    if (event.key.code == sfKeyA)
        game->lvl_vars->adress = &player->tower_buttons[DMG];
    if (event.key.code == sfKeyZ)
        game->lvl_vars->adress = &player->tower_buttons[DOT];
}

void events_keyboard(game_s *game, sfEvent event)
{
    player_t *player = game->lvl_vars->player;

    events_keyboard2(game, event);
    if (event.key.code == sfKeyE)
        game->lvl_vars->adress = &player->tower_buttons[SLOW];
    if (event.key.code == sfKeyR)
        game->lvl_vars->adress = &player->tower_buttons[HEAVY];
}

void events_lvl(game_s *game, sfEvent event)
{
    if (event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseRight)
        game->lvl_vars->adress = 0;
    for (int i = 0; i < 4; i++)
        events_buttons_scale(game, event, i);
    events_tower_mouse(game, event);
    (event.type == sfEvtKeyPressed) ? (events_keyboard(game, event)) : (0);
    (event.type == sfEvtMouseButtonReleased &&
    event.mouseButton.button == sfMouseLeft) ? (place_tower(game)) : (0);
    mod_scale(game->start_button->sprite, 1);
    if (collision_cursor(game->lvl_vars->cursor,
        game->start_button) == 1)
        mod_scale(game->start_button->sprite, 1.2);
    if (is_left_click(event, game->lvl_vars->cursor,
        game->start_button) == 1) {
        game->start = 1;
        sfMusic_play(game->beep);
    }
}
