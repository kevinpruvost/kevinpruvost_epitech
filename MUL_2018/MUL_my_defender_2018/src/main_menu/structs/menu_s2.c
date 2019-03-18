/*
** EPITECH PROJECT, 2019
** menu_s2.c
** File description:
** menu_s funcs 2
*/

#include "my.h"
#include "struct.h"
#include "libs.h"

game_obj *create_sprite_bgd(sfClock *clock)
{
    game_obj *sprite_bgd = malloc(sizeof(game_obj));
    sfIntRect rect = {0, 0, 200, 50};
    sfVector2f pos = {-600, 775};

    sprite_bgd = create_game_obj("assets/sprites/full.png", rect, pos, clock);
    return (sprite_bgd);
}

game_obj *create_cursor(sfClock *clock)
{
    game_obj *cursor = malloc(sizeof(game_obj));
    sfIntRect rect = {0, 0, 32, 32};
    sfVector2f pos = {500, 500};
    sfVector2f origin = {rect.width / 2, rect.height / 2};

    cursor = create_game_obj("assets/sprites/cursor.png", rect, pos, clock);
    cursor->origin = origin;
    sfSprite_setOrigin(cursor->sprite, origin);
    return (cursor);
}
