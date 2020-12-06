/*
** EPITECH PROJECT, 2018
** my_defender
** File description:
** my_defender
*/

#include "my.h"

void event_main_menu_set_buttons(game_s *game)
{
    sfSprite_setScale(game->mm_vars->play_button->sprite,
    game->mm_vars->play_button->scale);
    sfSprite_setScale(game->mm_vars->htp_button->sprite,
    game->mm_vars->htp_button->scale);
    sfSprite_setScale(game->mm_vars->quit_button->sprite,
    game->mm_vars->quit_button->scale);
    sfSprite_setScale(game->mm_vars->map_editor_button->sprite,
    game->mm_vars->map_editor_button->scale);
    sfSprite_setScale(game->mm_vars->settings_button->sprite,
    game->mm_vars->settings_button->scale);
}

void event_main_menu_move_cursor(game_s *game)
{
    sfVector2i local_pos = sfMouse_getPositionRenderWindow(game->win);

    game->mm_vars->cursor->pos.x = local_pos.x;
    game->mm_vars->cursor->pos.y = local_pos.y;
    game->lvl_vars->cursor->pos.x = local_pos.x;
    game->lvl_vars->cursor->pos.y = local_pos.y;
    game->maped_vars->cursor->pos.x = local_pos.x;
    game->maped_vars->cursor->pos.y = local_pos.y;
    sfSprite_setPosition(game->mm_vars->cursor->sprite,
    game->mm_vars->cursor->pos);
    sfSprite_setPosition(game->maped_vars->cursor->sprite,
    game->maped_vars->cursor->pos);
    sfSprite_setPosition(game->lvl_vars->cursor->sprite,
    game->lvl_vars->cursor->pos);
    event_main_menu_mod_buttons(game);
}

void events_main_menu3(game_s *game, sfEvent event)
{
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->play_button) == 1
        && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft) {
        sfMusic_play(game->beep);
        change_page(game, LEVEL);
        game->start = 0;
        }
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->htp_button) == 1
        && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft) {
        sfMusic_play(game->beep);
        change_page(game, HTP);
    }
}

void events_main_menu2(game_s *game, sfEvent event)
{
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->map_editor_button) == 1
        && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft) {
        sfMusic_play(game->beep);
        change_page(game, MAP_EDITOR);
    }
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->settings_button) == 1
        && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft) {
        sfMusic_play(game->beep);
        change_page(game, SETTINGS);
    }
    if (collision_cursor(game->mm_vars->cursor,
        game->mm_vars->quit_button) == 1
        && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft)
        sfRenderWindow_close(game->win);
}

void events_main_menu(game_s *game)
{
    sfEvent event;

    event_main_menu_move_cursor(game);
    while (sfRenderWindow_pollEvent(game->win, &event)) {
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyEscape)
            sfRenderWindow_close(game->win);
        events_main_menu3(game, event);
        events_main_menu2(game, event);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(game->win);
    }
}
