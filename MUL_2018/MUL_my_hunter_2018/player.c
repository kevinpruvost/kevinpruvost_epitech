/*
** EPITECH PROJECT, 2018
** player.c
** File description:
** player functions
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

sfVector2f move_crosshair(sfVector2f pos, sfSprite *cross, sfRenderWindow *win)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(win);

    pos.x = mouse_pos.x - 20;
    pos.y = mouse_pos.y - 20;
    sfSprite_setPosition(cross, pos);
    return (pos);
}

cross_prop set_cross_props(cross_prop cross, win_prop *w_prop, sounds *s_prop)
{
    cross.sprite = set_crosshair(w_prop->width, w_prop->height, w_prop);
    cross.clock = sfClock_create();
    cross.sound = s_prop->shot;
    return (cross);
}
