/*
** EPITECH PROJECT, 2019
** button.c
** File description:
** button map editor funcs
*/

#include "my.h"

game_obj *create_clear_button(sfClock *clock)
{
    game_obj *clear_button = malloc(sizeof(game_obj));
    sfVector2f clear_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 150;
    rect.height = 75;
    clear_button_pos.x = 150;
    clear_button_pos.y = 890;
    clear_button = create_game_obj("assets/sprites/clear_button.png", rect,
    clear_button_pos, clock);
    clear_button->origin.x = rect.width / 2;
    clear_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(clear_button->sprite, clear_button->origin);
    mod_scale(clear_button->sprite, 0.75);
    return (clear_button);
}

game_obj *create_random_button(sfClock *clock)
{
    game_obj *random_button = malloc(sizeof(game_obj));
    sfVector2f random_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 150;
    rect.height = 75;
    random_button_pos.x = 400;
    random_button_pos.y = 890;
    random_button = create_game_obj("assets/sprites/random_button.png", rect,
    random_button_pos, clock);
    random_button->origin.x = rect.width / 2;
    random_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(random_button->sprite, random_button->origin);
    mod_scale(random_button->sprite, 0.75);
    return (random_button);
}

game_obj *create_remove_button(sfClock *clock)
{
    game_obj *remove_button = malloc(sizeof(game_obj));
    sfVector2f remove_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 150;
    rect.height = 75;
    remove_button_pos.x = 650;
    remove_button_pos.y = 890;
    remove_button = create_game_obj("assets/sprites/remove_button.png", rect,
    remove_button_pos, clock);
    remove_button->origin.x = rect.width / 2;
    remove_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(remove_button->sprite, remove_button->origin);
    mod_scale(remove_button->sprite, 0.75);
    return (remove_button);
}

game_obj *create_not_valid(sfClock *clock)
{
    game_obj *remove_button = malloc(sizeof(game_obj));
    sfVector2f remove_button_pos;
    sfIntRect rect = {0, 0, 0, 0};
    sfColor color = {255, 255, 255, 0};

    rect.width = 200;
    rect.height = 87;
    remove_button_pos.x = 500;
    remove_button_pos.y = 350;
    remove_button = create_game_obj("assets/sprites/map_not_valid.png", rect,
    remove_button_pos, clock);
    remove_button->origin.x = rect.width / 2;
    remove_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(remove_button->sprite, remove_button->origin);
    mod_scale(remove_button->sprite, 2);
    sfSprite_setColor(remove_button->sprite, color);
    return (remove_button);
}
