/*
** EPITECH PROJECT, 2018
** window_processes.c
** File description:
** where the game works
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

void check_clean_window(win_prop *w_prop, game_info *game_infos, int *end)
{
    while (sfRenderWindow_pollEvent(w_prop->window, &w_prop->event)) {
        if (w_prop->event.type == sfEvtClosed)
            *end = 1;
        if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
            *end = 1;
        if (game_infos->AMMO == 0)
            *end = 1;
    }
    sfRenderWindow_clear(w_prop->window, sfTransparent);
    clear_framebuffer(w_prop->width, w_prop->height, w_prop->fb);
}

void render_window(win_prop *w_prop, back_prop bk, duck_prop dk, game_info *gm)
{
    char *final_score;

    sfRenderWindow_drawSprite(w_prop->window, bk.fond, NULL);
    sfRenderWindow_drawSprite(w_prop->window, dk.sprite, NULL);
    sfRenderWindow_drawSprite(w_prop->window, bk.background, NULL);
    final_score = str_add("Score : ", my_getnbr(gm->score));
    sfText_setString(bk.score_text, final_score);
    render_ammo(w_prop, gm);
    sfRenderWindow_drawText(w_prop->window, bk.score_text, NULL);
}

back_prop set_background_props(back_prop back, win_prop *w_prop)
{
    int wi = w_prop->width;
    int he = w_prop->height;

    back.background = set_background(w_prop->width, w_prop->height, w_prop);
    back.fond = set_fond(w_prop->width, w_prop->height, w_prop);
    back.score_text = scoretext_creation(back.score_text, wi, he);
    return (back);
}

void data_change(win_prop *w_prop, duck_prop *dk, cross_prop *cr, game_info *gm)
{
    if (is_timepassed(dk->clock_anim, 1.0/10.0) == 1)
        move_rect(&dk->rect, 110, 330);
    sfSprite_setTextureRect(dk->sprite, dk->rect);
    sfSprite_setPosition(dk->sprite, dk->position);
    dk->position = duck_movements(dk, w_prop);
    cr->position = move_crosshair(cr->position, cr->sprite, w_prop->window);
    if (sfMouse_isButtonPressed(sfMouseLeft) == sfTrue)
        dk->position = shoot(*cr, w_prop, gm, dk);
}
