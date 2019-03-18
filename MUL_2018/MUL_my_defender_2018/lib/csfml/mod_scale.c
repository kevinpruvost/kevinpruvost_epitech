/*
** EPITECH PROJECT, 2019
** mod_scale.c
** File description:
** mod scale funcs
*/

#include "my.h"

void mod_scale(sfSprite *sprite, float n)
{
    sfVector2f scale;

    scale.x = n;
    scale.y = n;
    sfSprite_setScale(sprite, scale);
}
