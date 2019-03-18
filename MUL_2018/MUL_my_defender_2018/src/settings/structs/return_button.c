/*
** EPITECH PROJECT, 2019
** return_button.c
** File description:
** return button for settings menu
*/

#include "my.h"

game_obj *create_return_button_sett(sfClock *clock)
{
    game_obj *return_button;
    sfIntRect rect = {0, 0, 200, 100};
    sfVector2f pos = {850, 875};

    return_button = create_game_obj
        ("assets/sprites/return_htp_sprite.png", rect, pos, clock);
    return_button->origin.x = rect.width / 2;
    return_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(return_button->sprite, return_button->origin);
    return (return_button);
}
