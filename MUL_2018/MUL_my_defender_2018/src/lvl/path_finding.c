/*
** EPITECH PROJECT, 2019
** path_finding.c
** File description:
** path finding for the mobs
*/

#include "my.h"

int count_end_path(order_t **map)
{
    int i = 0;

    for (i = 1; map[i]->order != 0; i++);
    i--;
    return (i);
}

int sens_vert_mobs_move(order_t *map, mob_t *mobs, int sens)
{
    float coeff = 1;

    (mobs->slow == 1) ? (coeff = 0.6) : (0);
    if (mobs->props->pos.x == map->x * 100 &&
        mobs->props->pos.y != map->y * 100) {
        (mobs->props->pos.y > map->y * 100) ? (sens = -1) : (0);
        mobs->props->pos.y += sens * 30 * mobs->speed
            * mobs->props->time_move->seconds * coeff;
        if (mobs->props->pos.y > map->y * 100 && sens == 1)
            mobs->props->pos.y = map->y * 100;
        if (mobs->props->pos.y < map->y * 100 && sens == -1)
            mobs->props->pos.y = map->y * 100;
        return (0);
    }
    return (84);
}

int sens_hor_mobs_move(order_t *map, mob_t *mobs, int sens)
{
    float coeff = 1;
    sfIntRect rect = sfSprite_getTextureRect(mobs->props->sprite);

    (mobs->slow == 1) ? (coeff = 0.6) : (0);
    if (mobs->props->pos.y == map->y * 100 &&
        mobs->props->pos.x != map->x * 100) {
        (mobs->props->pos.x > map->x * 100) ? (sens = -1) : (0);
        mobs->props->pos.x += sens * 30 * mobs->speed
            * mobs->props->time_move->seconds * coeff;
        (sens == 1) ? (rect.top = 0) : (rect.top = rect.width);
        if (mobs->props->pos.x > map->x * 100 && sens == 1)
            mobs->props->pos.x = map->x * 100;
        if (mobs->props->pos.x < map->x * 100 && sens == -1)
            mobs->props->pos.x = map->x * 100;
        mobs->props->rect = rect;
        sfSprite_setTextureRect(mobs->props->sprite, mobs->props->rect);
        return (0);
    }
    return (84);
}

void end_move(mob_t *mobs)
{
    float posy_final = 600;

    if (mobs->arrived == 0)
        mobs->props->pos.y += 1 * 30 * mobs->speed
            * mobs->props->time_move->seconds;
    if (mobs->props->pos.y > posy_final)
        mobs->props->pos.y = posy_final;
    if (mobs->props->pos.y == posy_final)
        mobs->arrived = 1;
}

void mobs_move(game_s *game)
{
    order_t **map = game->map->orders;
    mob_t *mobs = game->lvl_vars->mobs;
    int sens = 1;
    int end_path = count_end_path(map);

    for (int p_follow = 0, ret = 0; mobs != NULL; mobs = mobs->next, ret = 0) {
        p_follow = mobs->path_pos + 1;
        get_time(mobs->props->time_move, game->clock);
        ret = sens_vert_mobs_move(map[p_follow], mobs, sens);
        (ret == 84) ?
            (ret = sens_hor_mobs_move(map[p_follow], mobs, sens)) : (0);
        if (mobs->path_pos != end_path && ret == 84)
            mobs->path_pos += 1;
        if (mobs->path_pos == end_path)
            end_move(mobs);
        reset_time(mobs->props->time_move, game->clock);
        sfSprite_setPosition(mobs->props->sprite, mobs->props->pos);
    }
}
