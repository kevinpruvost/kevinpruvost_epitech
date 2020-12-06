/*
** EPITECH PROJECT, 2019
** events.c
** File description:
** events for map editor
*/

#include "my.h"

void event_buttons_map_editor_2(game_s *game)
{
    sfVector2i local_pos = sfMouse_getPositionRenderWindow(game->win);
    map_editor_s *maped_vars = game->maped_vars;

    maped_vars->random_desc->pos.x = local_pos.x;
    maped_vars->random_desc->pos.y = local_pos.y;
    maped_vars->remove_desc->pos.x = local_pos.x;
    maped_vars->remove_desc->pos.y = local_pos.y;
    maped_vars->clear_desc->pos.x = local_pos.x;
    maped_vars->clear_desc->pos.y = local_pos.y;
    maped_vars->return_desc->pos.x = local_pos.x;
    maped_vars->return_desc->pos.y = local_pos.y;
    sfSprite_setPosition(maped_vars->remove_desc->sprite,
    maped_vars->remove_desc->pos);
    sfSprite_setPosition(maped_vars->random_desc->sprite,
    maped_vars->random_desc->pos);
    sfSprite_setPosition(maped_vars->clear_desc->sprite,
    maped_vars->clear_desc->pos);
    sfSprite_setPosition(maped_vars->return_desc->sprite,
    maped_vars->return_desc->pos);
}

void event_buttons_map_editor_1(game_s *game)
{
    if (collision_cursor(game->maped_vars->cursor,
        game->maped_vars->remove_button) == 1) {
        mod_scale(game->maped_vars->remove_button->sprite, 1);
        set_visible(game->maped_vars->remove_desc->sprite);
    } else {
        mod_scale(game->maped_vars->remove_button->sprite, 0.75);
        set_invisible(game->maped_vars->remove_desc->sprite);
    }
    if (collision_cursor(game->maped_vars->cursor,
        game->maped_vars->random_button) == 1) {
        mod_scale(game->maped_vars->random_button->sprite, 1);
        set_visible(game->maped_vars->random_desc->sprite);
    } else {
        mod_scale(game->maped_vars->random_button->sprite, 0.75);
        set_invisible(game->maped_vars->random_desc->sprite);
    }
}

void event_buttons_map_editor_3(game_s *game, sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(game->win);
    if (collision_cursor(game->maped_vars->cursor,
        game->maped_vars->clear_button) == 1) {
        mod_scale(game->maped_vars->clear_button->sprite, 1);
        set_visible(game->maped_vars->clear_desc->sprite);
    } else {
        mod_scale(game->maped_vars->clear_button->sprite, 0.75);
        set_invisible(game->maped_vars->clear_desc->sprite);
    }
    if (collision_cursor(game->maped_vars->cursor,
        game->maped_vars->return_button) == 1 &&
        is_map_finished(game) == 0) {
        set_visible(game->maped_vars->return_desc->sprite);
    } else
        set_invisible(game->maped_vars->return_desc->sprite);
}

void event_buttons_map_editor_4(game_s *game, sfEvent event)
{
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyEscape &&
        is_map_finished(game) == 1 && playable_map(game) == 1)
        change_page_back(game);
    if (is_left_click(event, game->maped_vars->cursor,
        game->maped_vars->clear_button) == 1) {
        clear_map(game->map);
        sfMusic_play(game->beep);
    }
    if (is_left_click(event, game->maped_vars->cursor,
        game->maped_vars->random_button) == 1) {
        regenerate_random_map(game->map);
        sfMusic_play(game->beep);
    }
    if (is_left_click(event, game->maped_vars->cursor,
        game->maped_vars->remove_button) == 1) {
        remove_case(game);
        sfMusic_play(game->beep);
    }
}
