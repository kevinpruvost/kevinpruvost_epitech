/*
** EPITECH PROJECT, 2019
** funcs.c
** File description:
** main funcs for htp
*/

#include "my.h"

void draw_htp(game_s *game)
{
    sfRenderWindow_clear(game->win, sfTransparent);
    sfRenderWindow_drawSprite(game->win,
    game->htp_vars->background->sprite, NULL);
    sfRenderWindow_drawSprite(game->win, game->htp_vars->button->sprite, NULL);
    sfRenderWindow_drawSprite(game->win, game->htp_vars->cursor->sprite, NULL);
    sfRenderWindow_display(game->win);
}

void htp_change(game_s *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->win, &event)) {
        if (collision_cursor(game->htp_vars->cursor, game->htp_vars->button) ==
        1 && event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft) {
            sfMusic_play(game->beep);
            change_page_back(game);
        }
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyEscape)
            change_page_back(game);
    }
}

void event_htp(game_s *game)
{
    sfVector2i local_pos = sfMouse_getPositionRenderWindow(game->win);

    game->htp_vars->cursor->pos.x = local_pos.x;
    game->htp_vars->cursor->pos.y = local_pos.y;
    sfSprite_setPosition(game->htp_vars->cursor->sprite,
    game->htp_vars->cursor->pos);
    htp_change(game);
    window_check(game->win);
    if (collision_cursor(game->htp_vars->cursor, game->htp_vars->button) ==
    1) {
        game->htp_vars->button->scale.x = 1.25;
        game->htp_vars->button->scale.y = 1.25;
    } else {
        game->htp_vars->button->scale.x = 1;
        game->htp_vars->button->scale.y = 1;
    }
    sfSprite_setScale(game->htp_vars->button->sprite,
    game->htp_vars->button->scale);
}
