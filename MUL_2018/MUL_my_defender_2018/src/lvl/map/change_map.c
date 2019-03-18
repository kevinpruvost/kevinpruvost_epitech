/*
** EPITECH PROJECT, 2019
** change_map.c
** File description:
** funcs who change the sprites
*/

#include "my.h"

void change_map_2(game_obj *map_case)
{
    map_case->texture = sfTexture_createFromFile
        ("assets/sprites/chemin2.png", NULL);
    sfSprite_setTexture(map_case->sprite, map_case->texture, sfTrue);
}

void change_map_3(game_obj *map_case)
{
    map_case->texture = sfTexture_createFromFile
        ("assets/sprites/chemin3.png", NULL);
    sfSprite_setTexture(map_case->sprite, map_case->texture, sfTrue);
}

void change_map_4(game_obj *map_case)
{
    map_case->texture = sfTexture_createFromFile
        ("assets/sprites/chemin4.png", NULL);
    sfSprite_setTexture(map_case->sprite, map_case->texture, sfTrue);
}

void change_map_5(game_obj *map_case)
{
    map_case->texture = sfTexture_createFromFile
        ("assets/sprites/chemin5.png", NULL);
    sfSprite_setTexture(map_case->sprite, map_case->texture, sfTrue);
}

void change_map_6(game_obj *map_case)
{
    map_case->texture = sfTexture_createFromFile
        ("assets/sprites/chemin6.png", NULL);
    sfSprite_setTexture(map_case->sprite, map_case->texture, sfTrue);
}
