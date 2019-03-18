/*
** EPITECH PROJECT, 2019
** button.c
** File description:
** create button struct
*/

#include "my.h"

game_obj *create_htp_return_button(sfClock *clock)
{
    game_obj *htp_button = malloc(sizeof(game_obj));
    sfVector2f htp_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 100;
    htp_button_pos.x = 855;
    htp_button_pos.y = 890;
    htp_button = create_game_obj("assets/sprites/return_htp_sprite.png", rect,
    htp_button_pos, clock);
    htp_button->origin.x = rect.width / 2;
    htp_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(htp_button->sprite, htp_button->origin);
    return (htp_button);
}
