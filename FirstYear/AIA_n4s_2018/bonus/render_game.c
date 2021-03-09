/*
** EPITECH PROJECT, 2019
** render_game.c
** File description:
** render game
*/

#include "bonus.h"

void draw_game(window_t *b)
{
    sfRenderWindow_drawSprite(b->win, b->bgd->sprite, NULL);
    sfRenderWindow_drawSprite(b->win, b->stop->sprite, NULL);
    for (int i = 0; i < 4; i++)
        sfRenderWindow_drawSprite(b->win, b->keys[i]->sprite, NULL);
    sfRenderWindow_drawText(b->win, b->speed, NULL);
    sfRenderWindow_drawText(b->win, b->rotation, NULL);
    sfRenderWindow_drawSprite(b->win, b->exit_button->sprite, NULL);
    sfRenderWindow_drawSprite(b->win, b->cursor->sprite, NULL);
}

void mouse_follow(window_t *b)
{
    sfVector2i posi = sfMouse_getPositionRenderWindow(b->win);
    sfVector2f posf = {posi.x, posi.y};

    obj_set_position(b->cursor, posf.x, posf.y);
}

int render_game(window_t *b, ai_t *w)
{
    sfRenderWindow_clear(b->win, sfBlue);
    sfRenderWindow_pollEvent(b->win, &b->event);
    mouse_follow(b);
    actions_and_events(b, w);
    draw_game(b);
    sfRenderWindow_display(b->win);
    if (b->event.type == sfEvtClosed || KEY_R(sfKeyEscape))
        sfRenderWindow_close(b->win);
    if (b->event.type == sfEvtKeyReleased) {
        b->event.type = 1;
    }
    return (0);
}
