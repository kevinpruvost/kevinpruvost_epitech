/*
** EPITECH PROJECT, 2019
** proj_move.c
** File description:
** proj moving functions
*/

#include "my.h"

sfVector2f move_proj_h(proj_t *proj, int sx, sfVector2f posp, sfVector2f posm)
{
    (posp.x < posm.x) ? (sx = 1) : (0);
    (posp.x > posm.x) ? (sx = -1) : (0);
    posp.x += proj->props->time_move->seconds * 60 * proj->speed * sx;
    (posp.x > posm.x && sx == 1) ? (posp.x = posm.x) : (0);
    (posp.x < posm.x && sx == -1) ? (posp.x = posm.x) : (0);
    return (posp);
}

sfVector2f move_proj_v(proj_t *proj, int sy, sfVector2f posp, sfVector2f posm)
{
    (posp.y < posm.y) ? (sy = 1) : (0);
    (posp.y > posm.y) ? (sy = -1) : (0);
    posp.y += proj->props->time_move->seconds * 60 * proj->speed * sy;
    (posp.y > posm.y && sy == 1) ? (posp.y = posm.y) : (0);
    (posp.y < posm.y && sy == -1) ? (posp.y = posm.y) : (0);
    return (posp);
}

void move_proj_to_mob(proj_t *proj, mob_t *mob, sfClock *clock)
{
    sfVector2f posp = proj->props->pos;
    sfVector2f posm = mob->props->pos;
    int sx = 0;
    int sy = 0;

    get_time(proj->props->time_move, clock);
    posp = move_proj_h(proj, sx, posp, posm);
    posp = move_proj_v(proj, sy, posp, posm);
    proj->props->pos = posp;
    sfSprite_setPosition(proj->props->sprite, posp);
    if (posp.x <= posm.x + 2 && posp.x >= posm.x - 2
        && posp.y <= posm.y + 2 && posp.y >= posm.y - 2)
        proj->arrived = 1;
    reset_time(proj->props->time_move, clock);
}
