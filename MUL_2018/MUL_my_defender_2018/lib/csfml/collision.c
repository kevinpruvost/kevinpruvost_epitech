/*
** EPITECH PROJECT, 2019
** collision.c
** File description:
** collision
*/

#include "my.h"
#include "struct.h"
#include "libs.h"

collision_t *create_collision_struct(game_obj *obj1, game_obj *obj2)
{
    collision_t *coll = malloc(sizeof(collision_t));

    coll->x01 = obj1->pos.x - obj1->origin.x;
    coll->x02 = obj1->pos.x - obj1->origin.x + obj1->rect.width;
    coll->x11 = obj2->pos.x - obj2->origin.x;
    coll->x12 = obj2->pos.x - obj2->origin.x + obj2->rect.width;
    coll->y01 = obj1->pos.y - obj1->origin.y;
    coll->y02 = obj1->pos.y - obj1->origin.y + obj1->rect.height;
    coll->y11 = obj2->pos.y - obj2->origin.y;
    coll->y12 = obj2->pos.y - obj2->origin.y + obj2->rect.height;
    return (coll);
}

int collision_cursor(game_obj *cursor, game_obj *obj)
{
    collision_t *coll = create_collision_struct(cursor, obj);
    float x0 = (coll->x01 + coll->x02) / 2;
    float y0 = (coll->y01 + coll->y02) / 2;

    if (x0 >= coll->x11 && x0 <= coll->x12 &&
        y0 >= coll->y11 && y0 <= coll->y12) {
        free(coll);
        return (1);
    }
    if (x0 >= coll->x11 && x0 <= coll->x12 &&
        y0 >= coll->y11 && y0 <= coll->y12) {
        free(coll);
        return (1);
    }
    free(coll);
    return (0);
}

int collision_entities(game_obj *obj1, game_obj *obj2)
{
    int collision_x = 0;
    int collision_y = 0;
    collision_t *coll = create_collision_struct(obj1, obj2);

    if ((coll->x01 >= coll->x11 && coll->x01 <= coll->x12) ||
        (coll->x02 >= coll->x11 && coll->x02 <= coll->x12))
        collision_x = 1;
    if ((coll->y01 >= coll->y11 && coll->y01 <= coll->y12) ||
        (coll->y02 >= coll->y11 && coll->y02 <= coll->y12))
        collision_y = 1;
    free(coll);
    if (collision_x == 1 && collision_y == 1)
        return (1);
    return (0);
}
