/*
** EPITECH PROJECT, 2019
** lib_types.c
** File description:
** lib types struct
*/

#include "my.h"

void lib_types_tower(lib_types_t *lib_types)
{
    lib_types->damage_tower[DMG] = 20;
    lib_types->damage_tower[DOT] = 8;
    lib_types->damage_tower[SLOW] = 8;
    lib_types->damage_tower[HEAVY] = 45;
    lib_types->range_tower[0] = 100;
    lib_types->range_tower[1] = 150;
    lib_types->range_tower[2] = 100;
    lib_types->range_tower[3] = 150;
    lib_types->atk_speed_tower[0] = 1.5;
    lib_types->atk_speed_tower[1] = 2.5;
    lib_types->atk_speed_tower[2] = 3;
    lib_types->atk_speed_tower[3] = 3.5;
}

lib_types_t *create_lib_types(void)
{
    lib_types_t *lib_types = malloc(sizeof(lib_types_t));

    lib_types_textures(lib_types);
    lib_types_tower(lib_types);
    lib_types->speed_mob[TANK] = 1.5;
    lib_types->speed_mob[NORM] = 2.5;
    lib_types->speed_mob[SPD] = 5;
    lib_types->speed_mob[BUFF] = 2.5;
    lib_types->hp_mob[0] = 500;
    lib_types->hp_mob[1] = 100;
    lib_types->hp_mob[2] = 40;
    lib_types->hp_mob[3] = 150;
    lib_types->price_tower[DMG] = 60;
    lib_types->price_tower[DOT] = 75;
    lib_types->price_tower[SLOW] = 100;
    lib_types->price_tower[HEAVY] = 125;
    return (lib_types);
}

void destroy_lib_types(lib_types_t *lib_types)
{
    for (int i = 0; i < 4; i++) {
        sfTexture_destroy(lib_types->texture_tower[i]);
        sfTexture_destroy(lib_types->texture_mob[i]);
        sfTexture_destroy(lib_types->texture_proj[i]);
    }
    free(lib_types);
}
