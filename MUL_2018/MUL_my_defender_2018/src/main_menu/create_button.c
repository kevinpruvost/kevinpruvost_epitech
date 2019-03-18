/*
** EPITECH PROJECT, 2019
** button
** File description:
** create_button
*/

#include "libs.h"
#include "my.h"
#include "struct.h"

game_obj *create_play_button(sfClock *clock)
{
    game_obj *play_button;
    sfVector2f play_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 200;
    play_button_pos.x = 145;
    play_button_pos.y = 650;
    play_button = create_game_obj("assets/sprites/buttons_sprite.png", rect,
    play_button_pos, clock);
    play_button->origin.x = rect.width / 2;
    play_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(play_button->sprite, play_button->origin);
    return (play_button);
}

game_obj *create_htp_button(sfClock *clock)
{
    game_obj *htp_button;
    sfVector2f htp_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 200;
    rect.left = 200;
    htp_button_pos.x = 495;
    htp_button_pos.y = 650;
    htp_button = create_game_obj("assets/sprites/buttons_sprite.png", rect,
    htp_button_pos, clock);
    htp_button->origin.x = rect.width / 2;
    htp_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(htp_button->sprite, htp_button->origin);
    return (htp_button);
}

game_obj *create_quit_button(sfClock *clock)
{
    game_obj *quit_button;
    sfVector2f quit_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 200;
    rect.left = 400;
    quit_button_pos.x = 820;
    quit_button_pos.y = 650;
    quit_button = create_game_obj("assets/sprites/buttons_sprite.png", rect,
    quit_button_pos, clock);
    quit_button->origin.x = rect.width / 2;
    quit_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(quit_button->sprite, quit_button->origin);
    return (quit_button);
}

game_obj *create_map_editor_button(sfClock *clock)
{
    game_obj *map_editor_button;
    sfVector2f map_editor_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 200;
    rect.height = 200;
    rect.left = 0;
    map_editor_button_pos.x = 330;
    map_editor_button_pos.y = 450;
    map_editor_button =
        create_game_obj("assets/sprites/button_map_editor.png",
                        rect, map_editor_button_pos, clock);
    map_editor_button->origin.x = rect.width / 2;
    map_editor_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(map_editor_button->sprite, map_editor_button->origin);
    return (map_editor_button);
}

game_obj *create_settings_button(sfClock *clock)
{
    game_obj *settings_button;
    sfVector2f settings_button_pos;
    sfIntRect rect = {0, 0, 0, 0};

    rect.width = 220;
    rect.height = 200;
    rect.left = 0;
    settings_button_pos.x = 660;
    settings_button_pos.y = 450;
    settings_button =
        create_game_obj("assets/sprites/button_settings.png",
                        rect, settings_button_pos, clock);
    settings_button->origin.x = rect.width / 2;
    settings_button->origin.y = rect.height / 2;
    sfSprite_setOrigin(settings_button->sprite, settings_button->origin);
    return (settings_button);
}
