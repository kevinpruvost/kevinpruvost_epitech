/*
** EPITECH PROJECT, 2019
** map_spriting.c
** File description:
** put every sprite in place
*/

#include "my.h"
#include "map_spriting.h"

void begin_map_spriting(map_t *map)
{
    int i = 1;
    int sens_x = 0;
    int sens_y = 0;

    sens_x = map->orders[i+1]->x - map->orders[i]->x;
    sens_y = map->orders[i+1]->y - map->orders[i]->y;
    if (sens_y == 1)
        change_map_1(map->map_case[map->orders[i]->x][map->orders[i]->y]);
    if (sens_x == 1)
        change_map_6(map->map_case[map->orders[i]->x][map->orders[i]->y]);
    if (sens_x == -1)
        change_map_5(map->map_case[map->orders[i]->x][map->orders[i]->y]);
}

void end_map_spriting(map_t *map, int i)
{
    int sens_x = 0;
    int sens_y = 0;

    sens_x = map->orders[i-1]->x - map->orders[i]->x;
    sens_y = map->orders[i-1]->y - map->orders[i]->y;
    if (sens_x == 0 && sens_y == -1)
        change_map_1(map->map_case[map->orders[i]->x][map->orders[i]->y]);
    if (sens_x == 1 && sens_y == 0)
        change_map_3(map->map_case[map->orders[i]->x][map->orders[i]->y]);
    if (sens_x == -1 && sens_y == 0)
        change_map_4(map->map_case[map->orders[i]->x][map->orders[i]->y]);
}

void map_spriting3(msp_t msp, map_t *map)
{
    int i = msp.i;

    if ((msp.sens_y1 == 1 && msp.sens_y2 == 1)
        || (msp.sens_y1 == -1 && msp.sens_y2 == -1))
        change_map_1(map->map_case[map->orders[i]->x][map->orders[i]->y]);
    if ((msp.sens_x1 == 1 && msp.sens_x2 == 1)
        || (msp.sens_x1 == -1 && msp.sens_x2 == -1))
        change_map_2(map->map_case[map->orders[i]->x][map->orders[i]->y]);
    if ((msp.sens_x2 == 1 && msp.sens_y1 == -1)
        || (msp.sens_x1 == -1 && msp.sens_y2 == 1))
        change_map_3(map->map_case[map->orders[i]->x][map->orders[i]->y]);
}

void map_spriting2(msp_t msp, map_t *map)
{
    int i = msp.i;

    map_spriting3(msp, map);
    if ((msp.sens_x2 == -1 && msp.sens_y1 == -1)
        || (msp.sens_x1 == 1 && msp.sens_y2 == 1))
        change_map_4(map->map_case[map->orders[i]->x][map->orders[i]->y]);
    if ((msp.sens_x2 == 1 && msp.sens_y1 == 1)
        || (msp.sens_x1 == -1 && msp.sens_y2 == -1))
        change_map_6(map->map_case[map->orders[i]->x][map->orders[i]->y]);
    if ((msp.sens_x2 == -1 && msp.sens_y1 == 1)
        || (msp.sens_x1 == 1 && msp.sens_y2 == -1))
        change_map_5(map->map_case[map->orders[i]->x][map->orders[i]->y]);
}

void map_spriting(map_t *map)
{
    msp_t msp;

    begin_map_spriting(map);
    for (msp.i = 2; map->orders[msp.i+1]->order == msp.i+1; msp.i++) {
        msp.sens_x1 = map->orders[msp.i]->x - map->orders[msp.i-1]->x;
        msp.sens_y1 = map->orders[msp.i]->y - map->orders[msp.i-1]->y;
        msp.sens_x2 = map->orders[msp.i+1]->x - map->orders[msp.i]->x;
        msp.sens_y2 = map->orders[msp.i+1]->y - map->orders[msp.i]->y;
        map_spriting2(msp, map);
    }
    end_map_spriting(map, msp.i);
}
