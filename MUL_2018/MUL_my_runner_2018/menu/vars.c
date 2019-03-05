/*
** EPITECH PROJECT, 2018
** main_menu_vars.c
** File description:
** main_menu vars creation
*/

#include "my.h"

text_obj *button1_create(sfVector2f scale)
{
    text_obj *text;
    sfVector2f pos = {270 * scale.x, 350 * scale.y};
    sfColor color = {103, 242, 17, 255};

    text = create_text_obj("JOUER", scale, pos, color);
    return (text);
}

text_obj *button2_create(sfVector2f scale)
{
    text_obj *text;
    sfVector2f pos = {270 * scale.x, 450 * scale.y};
    sfColor color = {103, 242, 17, 255};

    text = create_text_obj("QUITTER", scale, pos, color);
    return (text);
}

game_obj *cursor_create(sfVector2f scale)
{
    game_obj *cursor;
    sfIntRect rect = {0, 0, 64, 64};
    sfVector2f pos = {180 * scale.x, 340 * scale.y};

    cursor = create_game_obj("sprites/cursor.png", rect, pos, scale);
    return (cursor);
}

bgd_obj *back_create(sfVector2f scale)
{
    bgd_obj *bgd;
    sfIntRect rect = {0, 0, 800, 800};
    sfVector2f pos = {0, 0};

    bgd = create_bgd_obj("sprites/main_menu.jpg", rect, scale);
    return (bgd);
}

bgd_obj *create_image(w_prop *win)
{
    bgd_obj *gif;
    sfVector2f scale = win->scale;
    sfIntRect rect = {0, 0, 800, 800};

    gif = create_bgd_obj("sprites/gif_play.png", rect, scale);
    return (gif);
}
