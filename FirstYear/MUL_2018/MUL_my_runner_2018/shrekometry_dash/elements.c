/*
** EPITECH PROJECT, 2019
** elements.c
** File description:
** for bckgd and cursors
*/

#include "my.h"

int pause_delay(gm_vars *gm, w_prop *win)
{
    sfTime time = sfClock_getElapsedTime(gm->back2->clock);
    float seconds = time.microseconds / 1000000.0;

    if (seconds < 0.2)
        return (0);
    if (sfKeyboard_isKeyPressed(sfKeyP) == sfTrue && gm->pause == 0) {
        gm->pause = 1;
        sfClock_restart(gm->back2->clock);
    } else if (sfKeyboard_isKeyPressed(sfKeyP) == sfTrue && gm->pause >= 1) {
        gm->pause = 0;
        sfClock_restart(gm->back2->clock);
    }
}

void scene_movement(gm_vars *gm, w_prop *win)
{
    sfTime time = sfClock_getElapsedTime(gm->back1->clock);
    float seconds = time.microseconds / 1000000.0;

    pause_delay(gm, win);
    if (gm->pause == 0) {
        gm->back1->rect.left += seconds * gm->speed / 3.0;
        gm->back2->rect.left += seconds * gm->speed / 1.5;
        if (gm->back2->rect.left >= 1942)
            gm->back2->rect.left = 0;
        if (gm->back1->rect.left >= 800)
            gm->back1->rect.left = 0;
        sfSprite_setTextureRect(gm->back1->sprite, gm->back1->rect);
        sfSprite_setTextureRect(gm->back2->sprite, gm->back2->rect);
        animation_shrek_walk_jump(gm);
    }
    sfClock_restart(gm->back1->clock);
}

void cursor_point(gm_vars *gm, w_prop *win)
{
    sfVector2i posi = sfMouse_getPositionRenderWindow(win->win);
    sfVector2f pos = {posi.x, posi.y};
    sfVector2f origin = {32, 32};

    sfSprite_setOrigin(gm->cursor->sprite, origin);
    sfSprite_setPosition(gm->cursor->sprite, pos);
    sfRenderWindow_drawSprite(win->win, gm->cursor->sprite, NULL);
}

int move_block(game_obj *block, w_prop *win, gm_vars *gm)
{
    float seconds = clock_getseconds(block->clock);

    if (gm->pause >= 1) {
        sfClock_restart(block->clock);
        return (0);
    }
    block->pos.x -= gm->speed * seconds * win->scale.x;
    sfSprite_setPosition(block->sprite, block->pos);
    sfClock_restart(block->clock);
}

void draw_blocks(gm_vars *gm, w_prop *win)
{
    for (int i = 0; i < gm->map->height; i++)
        for (int j = 0; j < gm->map->width; j++) {
            sfRenderWindow_drawSprite(win->win,
            gm->map->blocks[i][j]->sprite, NULL);
            move_block(gm->map->blocks[i][j], win, gm);
        }
}
