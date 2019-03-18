/*
** EPITECH PROJECT, 2019
** funcs.c
** File description:
** main funcs of map editor
*/

#include "my.h"

void event_place_case(game_s *game, sfEvent event)
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            (collision_cursor(game->maped_vars->cursor,
            game->maped_vars->p_cases[i][j]) == 1
            && event.type == sfEvtMouseButtonReleased &&
            event.mouseButton.button == sfMouseLeft &&
            check_valid_case(game->maped_vars->p_cases[i][j]) == 1) ?
            (add_case(game, i, j)) : (0);
        }
    }
}

void event_buttons_map_editor(game_s *game, sfEvent event)
{
    event_buttons_map_editor_1(game);
    event_buttons_map_editor_2(game);
    event_buttons_map_editor_3(game, event);
    event_buttons_map_editor_4(game, event);
    if (is_left_click(event, game->maped_vars->cursor,
        game->maped_vars->return_button) == 1
        && is_map_finished(game) == 1 && playable_map(game) == 1) {
        change_page_back(game);
        sfMusic_play(game->beep);
    }
}

void event_map_editor3(game_s *game, sfEvent event)
{
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyR)
        regenerate_random_map(game->map);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyDelete)
        remove_case(game);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyC)
        clear_map(game->map);
}

void event_map_editor2(game_s *game, sfEvent event)
{
    sfColor grid_color = {0, 0, 0, 150};

    show_p_cases(game);
    while (sfRenderWindow_pollEvent(game->win, &event)) {
        event_buttons_map_editor(game, event);
        event_map_editor3(game, event);
        (playable_map(game) != 1) ?
        (set_visible(game->maped_vars->not_valid->sprite))
        : (set_invisible(game->maped_vars->not_valid->sprite));
        event_place_case(game, event);
        sfSprite_setColor(game->maped_vars->grid->sprite, grid_color);
    }
}

void event_map_editor(game_s *game)
{
    sfVector2i local_pos = sfMouse_getPositionRenderWindow(game->win);
    sfEvent event;

    event_map_editor2(game, event);
    window_check(game->win);
    game->maped_vars->cursor->pos.x = local_pos.x;
    game->maped_vars->cursor->pos.y = local_pos.y;
    sfSprite_setPosition(game->maped_vars->cursor->sprite,
    game->maped_vars->cursor->pos);
    if (collision_cursor(game->maped_vars->cursor,
        game->maped_vars->return_button) == 1)
        mod_scale(game->maped_vars->return_button->sprite, 1);
    else
        mod_scale(game->maped_vars->return_button->sprite, 0.75);
}
