/*
** EPITECH PROJECT, 2019
** menu_s.c
** File description:
** menu_s funcs
*/

#include "my.h"
#include "struct.h"
#include "libs.h"

void create_txt_menu(text_obj *ranks[3])
{
    sfColor co = {100, 255, 50, 200};
    sfVector2f sc = {1, 1};
    sfVector2f pos = {900, 59};
    sfFont *font = sfFont_createFromFile("assets/fonts/CELTICHD.TTF");

    ranks[0] = create_text_obj("Ah", sc, pos, co);
    pos.y += 63;
    ranks[1] = create_text_obj("Ah", sc, pos, co);
    pos.y += 69;
    ranks[2] = create_text_obj("Ah", sc, pos, co);
    for (int i = 0; i < 3; i++) {
        sfText_setCharacterSize(ranks[i]->text, 48);
        sfText_setFont(ranks[i]->text, font);
    }
}

menu_s *create_menu_s(sfClock *clock)
{
    menu_s *mm_vars = malloc(sizeof(menu_s));
    sfIntRect bgd_rect = {0, 0, 1000, 1000};
    sfVector2f bgd_scale = {1, 1};

    mm_vars->background = create_bgd_obj("assets/bgd/main_menu_bgd.png",
    bgd_rect, bgd_scale);
    mm_vars->sprite_bgd = create_sprite_bgd(clock);
    mm_vars->play_button = create_play_button(clock);
    mm_vars->htp_button = create_htp_button(clock);
    mm_vars->quit_button = create_quit_button(clock);
    mm_vars->map_editor_button = create_map_editor_button(clock);
    mm_vars->settings_button = create_settings_button(clock);
    mm_vars->cursor = create_cursor(clock);
    create_txt_menu(mm_vars->ranks);
    return (mm_vars);
}

void destroy_menu_s(menu_s *mm_vars)
{
    destroy_bgd_obj(mm_vars->background);
    destroy_game_obj(mm_vars->sprite_bgd);
    destroy_game_obj(mm_vars->play_button);
    destroy_game_obj(mm_vars->htp_button);
    destroy_game_obj(mm_vars->quit_button);
    destroy_game_obj(mm_vars->map_editor_button);
    destroy_game_obj(mm_vars->settings_button);
    destroy_game_obj(mm_vars->cursor);
    for (int i = 0; i < 3; i++)
        destroy_text_obj(mm_vars->ranks[i]);
    free(mm_vars);
}

menu_s *change_menu_s(menu_s *mm_vars, sfClock *clock)
{
    menu_s *mm_vars_new = create_menu_s(clock);

    destroy_menu_s(mm_vars);
    return (mm_vars_new);
}
