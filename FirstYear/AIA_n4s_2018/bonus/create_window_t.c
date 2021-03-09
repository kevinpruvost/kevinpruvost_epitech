/*
** EPITECH PROJECT, 2019
** create_window_t.c
** File description:
** create window
*/

#include "bonus.h"

void create_text_window_t(window_t *b)
{
    sfFont *font = sfFont_createFromFile("bonus/assets/font.ttf");
    sfColor color = {255, 255, 255, 255};

    b->speed = create_text("Vitesse : ", 25, font);
    b->rotation = create_text("Rotation : ", 25, font);
    edit_text(b->speed, "Vitesse : ", 50, 30);
    edit_text(b->rotation, "Rotation : ", 50, 100);
    sfText_setColor(b->speed, color);
    sfText_setColor(b->rotation, color);
    cut_animation(b->bgd, 12, 1);
}

int place_window_t_objs(window_t *b)
{
    b->exit_button = create_obj_t_sprite
    (b->clock, "bonus/assets/exit_button.png", NULL);
    if (b->exit_button == NULL)
        return (84);
    obj_set_position(b->exit_button, 500 / 10 * 8, 500 / 10 * 8.5);
    obj_set_position(b->stop, 500 / 10 * 7, 500 / 10 * 5.5);
    obj_set_position(b->keys[0], 500 / 10 * 2.5, 500 / 10 * 4);
    obj_set_position(b->keys[1], 500 / 10 * 1, 500 / 10 * 5.5);
    obj_set_position(b->keys[2], 500 / 10 * 2.5, 500 / 10 * 5.5);
    obj_set_position(b->keys[3], 500 / 10 * 4, 500 / 10 * 5.5);
    sprite_set_origin(b->bgd->sprite, 0, 0);
    sprite_set_origin(b->cursor->sprite, 0, 0);
    create_text_window_t(b);
    return (0);
}

int create_window_t_objs(window_t *b)
{
    b->cursor = create_obj_t_sprite
    (b->clock, "bonus/assets/cursor.png", NULL);
    b->stop = create_obj_t_sprite
    (b->clock, "bonus/assets/stop.png", NULL);
    b->keys[0] = create_obj_t_sprite
    (b->clock, "bonus/assets/z.png", NULL);
    b->keys[1] = create_obj_t_sprite
    (b->clock, "bonus/assets/q.png", NULL);
    b->keys[2] = create_obj_t_sprite
    (b->clock, "bonus/assets/s.png", NULL);
    b->keys[3] = create_obj_t_sprite
    (b->clock, "bonus/assets/d.png", NULL);
    b->bgd = create_obj_t_sprite
    (b->clock, "bonus/assets/bgd.png", NULL);
    if (b->cursor == NULL || b->stop == NULL ||
        b->keys[0] == NULL || b->keys[1] == NULL)
        return (84);
    if (b->keys[2] == NULL || b->keys[3] == NULL || b->bgd == NULL)
        return (84);
    return (place_window_t_objs(b));
}

window_t *create_window_t(ai_t *w)
{
    window_t *b = malloc(sizeof(window_t));
    char *name = "Commandes du Need4Stek";

    if (b == NULL)
        return (NULL);
    b->mode.width = 460;
    b->mode.height = 460;
    b->mode.bitsPerPixel = 32;
    b->win = sfRenderWindow_create(b->mode, name,
    sfResize | sfClose, NULL);
    sfRenderWindow_setMouseCursorVisible(b->win, sfFalse);
    sfRenderWindow_setFramerateLimit(b->win, 144);
    b->clock = sfClock_create();
    if (create_window_t_objs(b) == 84)
        return (NULL);
    return (b);
}

void destroy_window_t(window_t *b)
{
    for (int i = 0; i < 4; i++)
        destroy_obj_t(b->keys[i]);
    destroy_obj_t(b->cursor);
    destroy_obj_t(b->stop);
    destroy_obj_t(b->bgd);
    destroy_obj_t(b->exit_button);
    sfText_destroy(b->speed);
    sfText_destroy(b->rotation);
    if (sfRenderWindow_isOpen(b->win) == sfTrue)
        sfRenderWindow_close(b->win);
    sfRenderWindow_destroy(b->win);
    sfClock_destroy(b->clock);
    free(b);
}
