/*
** EPITECH PROJECT, 2019
** anim_sprite.c
** File description:
** anim sprite
*/

#include "my.h"

int anim_sprite(game_obj *obj, int anim_count)
{
    sfIntRect rect = sfSprite_getTextureRect(obj->sprite);
    int ret = 0;

    rect.left += rect.width;
    if (rect.left >= rect.width * anim_count) {
        rect.left = 0;
        ret = 1;
    }
    obj->rect = rect;
    sfSprite_setTextureRect(obj->sprite, rect);
    return (ret);
}
