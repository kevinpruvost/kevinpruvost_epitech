/*
** EPITECH PROJECT, 2018
** background_obj.c
** File description:
** background func
*/

#include "my.h"

bgd_obj *create_bgd_obj(char *sprite_file, sfIntRect rect, sfVector2f scale)
{
    bgd_obj *bgd = malloc(sizeof(bgd_obj));

    bgd->sprite = sfSprite_create();
    bgd->texture = sfTexture_createFromFile(sprite_file, NULL);
    bgd->rect = rect;
    sfSprite_setTexture(bgd->sprite, bgd->texture, sfFalse);
    sfSprite_setTextureRect(bgd->sprite, bgd->rect);
    bgd->pos.x = 0;
    bgd->pos.y = 0;
    sfSprite_setPosition(bgd->sprite, bgd->pos);
    bgd->clock = sfClock_create();
    bgd->scale = scale;
    sfSprite_setScale(bgd->sprite, scale);
    return (bgd);
}

void destroy_bgd_obj(bgd_obj *bgd)
{
    sfSprite_destroy(bgd->sprite);
    sfTexture_destroy(bgd->texture);
    sfClock_destroy(bgd->clock);
    free(bgd);
}
