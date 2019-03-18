/*
** EPITECH PROJECT, 2019
** map_editor_s.c
** File description:
** map_editor structs
*/

#include "my.h"

game_obj *create_maped_return_button(sfClock *clock)
{
    game_obj *htp_button = malloc(sizeof(game_obj));
    sfVector2f htp_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 100;
    htp_button_pos.x = 875;
    htp_button_pos.y = 890;
    htp_button = create_game_obj("assets/sprites/return_htp_sprite.png", rect,
    htp_button_pos, clock);
    htp_button->origin.x = rect.width / 2;
    htp_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(htp_button->sprite, htp_button->origin);
    return (htp_button);
}

map_editor_s *create_map_editor_s2(map_editor_s *maped_vars, sfClock *clock)
{
    sfVector2f pos = {0, 0};
    sfIntRect rect = {0, 0, 100, 100};

    maped_vars->not_valid = create_not_valid(clock);
    for (int i = 0; i < 10; i++, pos.x += 100, pos.y = 0)
        for (int j = 0; j < 6; j++) {
            maped_vars->p_cases[i][j] = create_game_obj
                ("assets/sprites/chemin1.png", rect, pos, clock);
            pos.y += 100;
        }
    return (maped_vars);
}

map_editor_s *create_map_editor_s(sfClock *clock)
{
    map_editor_s *maped_vars = malloc(sizeof(map_editor_s));
    sfIntRect bgd_rect = {0, 0, 1000, 1000};
    sfVector2f bgd_scale = {1, 1};

    maped_vars->background = create_bgd_obj("assets/bgd/maped_bgd.png",
                                            bgd_rect, bgd_scale);
    maped_vars->grid = create_grid();
    maped_vars->cursor = create_cursor(clock);
    maped_vars->clear_button = create_clear_button(clock);
    maped_vars->random_button = create_random_button(clock);
    maped_vars->remove_button = create_remove_button(clock);
    maped_vars->return_button = create_maped_return_button(clock);
    maped_vars->remove_desc = create_remove_desc(clock);
    maped_vars->random_desc = create_random_desc(clock);
    maped_vars->clear_desc = create_clear_desc(clock);
    maped_vars->return_desc = create_return_desc(clock);
    maped_vars = create_map_editor_s2(maped_vars, clock);
    return (maped_vars);
}

void destroy_map_editor_s(map_editor_s *maped_vars)
{
    destroy_game_obj(maped_vars->clear_button);
    destroy_game_obj(maped_vars->random_button);
    destroy_game_obj(maped_vars->remove_button);
    destroy_game_obj(maped_vars->clear_desc);
    destroy_game_obj(maped_vars->random_desc);
    destroy_game_obj(maped_vars->remove_desc);
    destroy_game_obj(maped_vars->return_desc);
    destroy_bgd_obj(maped_vars->background);
    destroy_bgd_obj(maped_vars->grid);
    destroy_game_obj(maped_vars->cursor);
    for (int i = 9; i >= 0; i--)
        for (int j = 5; j >= 0; j--)
            destroy_game_obj(maped_vars->p_cases[i][j]);
    free(maped_vars);
}
