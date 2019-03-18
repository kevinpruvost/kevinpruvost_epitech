/*
** EPITECH PROJECT, 2019
** lib_types_textures.c
** File description:
** textures
*/

#include "my.h"

void lib_types_textures2(lib_types_t *lib_types)
{
    lib_types->texture_proj[DMG] =
        sfTexture_createFromFile("assets/sprites/proj_fiona.png", NULL);
    lib_types->texture_proj[DOT] =
        sfTexture_createFromFile("assets/sprites/proj_shrek.png", NULL);
    lib_types->texture_proj[SLOW] =
        sfTexture_createFromFile("assets/sprites/proj_donkey.png", NULL);
    lib_types->texture_proj[HEAVY] =
        sfTexture_createFromFile("assets/sprites/proj_dragon.png", NULL);
}

void lib_types_textures(lib_types_t *lib_types)
{
    lib_types->texture_tower[DMG] =
        sfTexture_createFromFile("assets/sprites/fiona_sprite.png", NULL);
    lib_types->texture_tower[DOT] =
        sfTexture_createFromFile("assets/sprites/shrek_sprite.png", NULL);
    lib_types->texture_tower[SLOW] =
        sfTexture_createFromFile("assets/sprites/donkey_sprite.png", NULL);
    lib_types->texture_tower[HEAVY] =
        sfTexture_createFromFile("assets/sprites/dragon_sprite.png", NULL);
    lib_types->texture_mob[TANK] =
        sfTexture_createFromFile("assets/sprites/mob4.png", NULL);
    lib_types->texture_mob[NORM] =
        sfTexture_createFromFile("assets/sprites/mob1.png", NULL);
    lib_types->texture_mob[SPD] =
        sfTexture_createFromFile("assets/sprites/mob2.png", NULL);
    lib_types->texture_mob[BUFF] =
        sfTexture_createFromFile("assets/sprites/mob3.png", NULL);
    lib_types_textures2(lib_types);
}
