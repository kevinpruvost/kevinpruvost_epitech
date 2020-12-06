/*
** EPITECH PROJECT, 2019
** desc.c
** File description:
** desc for map editor buttons
*/

#include "my.h"

game_obj *create_clear_desc(sfClock *clock)
{
    game_obj *clear_desc = malloc(sizeof(game_obj));
    sfVector2f clear_desc_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 200;
    clear_desc_pos.x = 0;
    clear_desc_pos.y = 0;
    clear_desc = create_game_obj("assets/sprites/clear_desc.png", rect,
    clear_desc_pos, clock);
    clear_desc->origin.x = 0;
    clear_desc->origin.y = rect.height;
    sfSprite_setOrigin(clear_desc->sprite, clear_desc->origin);
    return (clear_desc);
}

game_obj *create_random_desc(sfClock *clock)
{
    game_obj *random_desc = malloc(sizeof(game_obj));
    sfVector2f random_desc_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 200;
    random_desc_pos.x = 0;
    random_desc_pos.y = 0;
    random_desc = create_game_obj("assets/sprites/random_desc.png", rect,
    random_desc_pos, clock);
    random_desc->origin.x = 0;
    random_desc->origin.y = rect.height;
    sfSprite_setOrigin(random_desc->sprite, random_desc->origin);
    return (random_desc);
}

game_obj *create_remove_desc(sfClock *clock)
{
    game_obj *remove_desc = malloc(sizeof(game_obj));
    sfVector2f remove_desc_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 200;
    remove_desc_pos.x = 0;
    remove_desc_pos.y = 0;
    remove_desc = create_game_obj("assets/sprites/remove_desc.png", rect,
                                    remove_desc_pos, clock);
    remove_desc->origin.x = 0;
    remove_desc->origin.y = rect.height;
    sfSprite_setOrigin(remove_desc->sprite, remove_desc->origin);
    return (remove_desc);
}

game_obj *create_return_desc(sfClock *clock)
{
    game_obj *return_desc = malloc(sizeof(game_obj));
    sfVector2f return_desc_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 200;
    return_desc_pos.x = 0;
    return_desc_pos.y = 0;
    return_desc = create_game_obj("assets/sprites/return_desc.png", rect,
    return_desc_pos, clock);
    return_desc->origin.x = rect.width;
    return_desc->origin.y = rect.height;
    sfSprite_setOrigin(return_desc->sprite, return_desc->origin);
    return (return_desc);
}
