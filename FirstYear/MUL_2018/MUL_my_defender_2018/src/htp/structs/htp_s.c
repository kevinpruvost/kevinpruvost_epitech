/*
** EPITECH PROJECT, 2019
** htp_s.c
** File description:
** htp structs
*/

#include "my.h"

htp_s *create_htp_s(sfClock *clock)
{
    htp_s *htp_vars = malloc(sizeof(htp_s));
    sfIntRect bgd_rect = {0, 0, 1000, 1000};
    sfVector2f bgd_scale = {1, 1};

    htp_vars->background = create_bgd_obj("assets/bgd/htp_bgd.png",
    bgd_rect, bgd_scale);
    htp_vars->cursor = create_cursor(clock);
    htp_vars->button = create_htp_return_button(clock);
    return (htp_vars);
}

void destroy_htp_s(htp_s *htp_vars)
{
    destroy_bgd_obj(htp_vars->background);
    destroy_game_obj(htp_vars->button);
    destroy_game_obj(htp_vars->cursor);
    free(htp_vars);
}

htp_s *change_htp_s(htp_s *htp_vars, sfClock *clock)
{
    htp_s *htp_vars_new = create_htp_s(clock);

    destroy_htp_s(htp_vars);
    return (htp_vars_new);
}
