/*
** EPITECH PROJECT, 2018
** set_vars.c
** File description:
** to set the struct vars
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

win_prop set_w_prop(win_prop w_prop, int wi, int he, float ips)
{
    char *name = "Canard Hunt";
    sfVideoMode mode = {wi, he, 32};

    w_prop.width = wi;
    w_prop.height = he;
    w_prop.fps = ips;
    w_prop.scale_x = wi / 800.0;
    w_prop.scale_y = wi / 800.0;
    w_prop.scale.x = w_prop.scale_x;
    w_prop.scale.y = w_prop.scale_y;
    w_prop.window = sfRenderWindow_create(mode, name, sfResize | sfClose, NULL);
    w_prop.fb = framebuffer_create(wi, he);
    return (w_prop);
}
