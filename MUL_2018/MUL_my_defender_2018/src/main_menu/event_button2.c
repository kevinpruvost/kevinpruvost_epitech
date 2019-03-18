/*
** EPITECH PROJECT, 2019
** event_button2.c
** File description:
** events buttons 2
*/

#include "my.h"

void event_main_menu_mod_buttons2(game_s *game)
{
    game->mm_vars->play_button->scale.x = 1;
    game->mm_vars->play_button->scale.y = 1;
    game->mm_vars->htp_button->scale.x = 1;
    game->mm_vars->htp_button->scale.y = 1;
    game->mm_vars->quit_button->scale.x = 1;
    game->mm_vars->quit_button->scale.y = 1;
    game->mm_vars->map_editor_button->scale.x = 1;
    game->mm_vars->map_editor_button->scale.y = 1;
    game->mm_vars->settings_button->scale.x = 1;
    game->mm_vars->settings_button->scale.y = 1;
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->play_button) == 1) {
        game->mm_vars->play_button->scale.x = 1.25;
        game->mm_vars->play_button->scale.y = 1.25;
    }
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->htp_button) == 1) {
        game->mm_vars->htp_button->scale.x = 1.25;
        game->mm_vars->htp_button->scale.y = 1.25;
    }
}

void event_main_menu_mod_buttons(game_s *game)
{
    event_main_menu_mod_buttons2(game);
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->quit_button) == 1) {
        game->mm_vars->quit_button->scale.x = 1.25;
        game->mm_vars->quit_button->scale.y = 1.25;
    }
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->map_editor_button) == 1) {
        game->mm_vars->map_editor_button->scale.x = 1.25;
        game->mm_vars->map_editor_button->scale.y = 1.25;
    }
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->settings_button) == 1) {
        game->mm_vars->settings_button->scale.x = 1.25;
        game->mm_vars->settings_button->scale.y = 1.25;
    }
    event_main_menu_set_buttons(game);
}
