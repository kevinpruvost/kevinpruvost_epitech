/*
** EPITECH PROJECT, 2019
** jump.c
** File description:
** for jump management
*/

#include "my.h"

void animation_shrek_walk_jump(gm_vars *gm)
{
    sfTime time = sfClock_getElapsedTime(gm->player->clock_anim);
    float seconds = time.microseconds / 1000000.0;

    if (seconds >= 1.0 / 5.0 && gm->player->jump_mode == 0 && gm->alive == 1) {
        gm->player->rect.top = 0;
        gm->player->rect.left += 43;
        if (gm->player->rect.left > 215)
            gm->player->rect.left = 0;
        sfSprite_setTextureRect(gm->player->sprite, gm->player->rect);
        sfClock_restart(gm->player->clock_anim);
    } else if (seconds >= 1.0 / 5.0 &&
    gm->player->jump_mode == 1 && gm->alive == 1) {
        gm->player->rect.top = 52;
        gm->player->rect.left += 43;
        if (gm->player->rect.left > 215 - 86)
            gm->player->rect.left = 0;
        sfSprite_setTextureRect(gm->player->sprite, gm->player->rect);
        sfClock_restart(gm->player->clock_anim);
    }
}

int jump_management(gm_vars *gm, w_prop *win)
{
    float seconds = clock_getseconds(gm->player->clock_jump);

    if (gm->pause >= 1) {
        sfClock_restart(gm->player->clock_jump);
        return (0);
    }
    if (sfKeyboard_isKeyPressed(sfKeySpace) == sfTrue
        && gm->player->jump_mode == 0) {
        gm->player->jump_mode = 1, gm->player->rect.left = 0;
        sfSound_play(gm->jump_sound->sound);
        sfClock_restart(gm->player->clock_jump);
    }
    if (gm->player->jump_mode == 0)
        sfClock_restart(gm->player->clock_jump);
    else {
        if (seconds >= 0.5) {
            gm->player->jump_mode = 2, gm->player->rect.left = 0;
            sfClock_restart(gm->player->clock_jump);
        }
    }
}

int gravity(gm_vars *gm, w_prop *win)
{
    sfTime time = sfClock_getElapsedTime(gm->gravity_clock);
    float seconds = time.microseconds / 1000000.0;

    if (gm->pause >= 1) {
        sfClock_restart(gm->gravity_clock);
        return (0);
    }
    if (gm->player->jump_mode == 1)
        gm->player->pos.y -= (575 * win->scale.y) * seconds;
    if (gm->player->pos.y < (gm->player->y_sol - 2 * 52)) {
        gm->player->pos.y += (225 * win->scale.y) * seconds;
        gm->player->rect.top = 52;
        gm->player->rect.left = 43 * 3;
    } else if (gm->player->jump_mode == 2)
        gm->player->jump_mode = 0;
    if (gm->player->pos.y >= (gm->player->y_sol - 2 * (52)))
        gm->player->pos.y = (gm->player->y_sol - 2 * (52));
    sfSprite_setPosition(gm->player->sprite, gm->player->pos);
    sfSprite_setTextureRect(gm->player->sprite, gm->player->rect);
    sfClock_restart(gm->gravity_clock);
}

int y_sol_management(gm_vars *gm, w_prop *win)
{
    int id_col = 0;
    int x_l = 80 * win->scale.x;
    int taille_y = gm->player->rect.height;
    int y_obst = 0;
    int j = 0;

    for (int i = 0; id_col == 0 && i < gm->map->width; i++)
        if (gm->map->blocks[0][i]->pos.x <= x_l * 2 &&
            gm->map->blocks[0][i]->pos.x >= x_l)
            id_col = i;
    for (int i = 0; gm->map->id_blocks[i][id_col] == 4; i++, j++) {
        gm->player->y_sol = gm->map->blocks[i][id_col]->pos.y + 80;
        y_obst = gm->map->blocks[i][id_col+1]->pos.y;
    }
    if (gm->player->pos.y >= y_obst)
        gm->alive = 0;
    if (gm->player->pos.y + 104 == (int)(gm->player->y_sol)
        && gm->map->id_blocks[j][id_col] == 2)
        gm->alive = 0;
    return (id_col);
}

void analyse_end(gm_vars *gm, w_prop *win)
{
    if (y_sol_management(gm, win) == gm->map->width - 10)
        gm->stop = 1;
}
