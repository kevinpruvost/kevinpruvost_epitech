/*
** EPITECH PROJECT, 2019
** center_game_object.c
** File description:
** center go
*/

#include "my.h"

void center_game_object(game_obj *game_obj)
{
    sfIntRect rect = sfSprite_getTextureRect(game_obj->sprite);
    sfVector2f origin = {rect.width / 2, rect.height / 2};

    game_obj->origin.x = origin.x;
    game_obj->origin.y = origin.y;
    game_obj->rect = rect;
    game_obj->origin = origin;
    sfSprite_setOrigin(game_obj->sprite, game_obj->origin);
}

void center_mob(game_obj *game_obj)
{
    sfIntRect rect = sfSprite_getTextureRect(game_obj->sprite);
    sfVector2f origin = {-(rect.width / 2), -(rect.height / 2)};

    game_obj->origin.x = origin.x;
    game_obj->origin.y = origin.y;
    game_obj->rect = rect;
    game_obj->origin = origin;
    sfSprite_setOrigin(game_obj->sprite, game_obj->origin);
}

void center_hp(game_obj *hp, game_obj *obj2)
{
    sfIntRect rect = sfSprite_getTextureRect(obj2->sprite);
    sfVector2f origin = {-(rect.width / 2), -(rect.height / 2)};

    obj2->origin.x = origin.x;
    obj2->origin.y = origin.y;
    hp->origin = origin;
    sfSprite_setOrigin(hp->sprite, hp->origin);
}
