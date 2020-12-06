/*
** EPITECH PROJECT, 2018
** background.c
** File description:
** to make the background
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

sfSprite *set_crosshair(int wi, int he, win_prop *w_prop)
{
    sfSprite *background = sfSprite_create();
    sfTexture *texture = sfTexture_create(wi, he);

    texture = sfTexture_createFromFile("sprites/crosshair.png", NULL);
    sfTexture_updateFromPixels(texture, w_prop->fb->pixels, wi, he, 400, 400);
    sfSprite_setTexture(background, texture, sfFalse);
    sfSprite_setScale(background, w_prop->scale);
    return (background);
}

sfSprite *set_duck(int wi, int he, win_prop *w_prop)
{
    sfSprite *background = sfSprite_create();
    sfTexture *texture = sfTexture_create(wi, he);

    texture = sfTexture_createFromFile("sprites/duck.png", NULL);
    sfTexture_updateFromPixels(texture, w_prop->fb->pixels, wi, he, 400, 400);
    sfSprite_setTexture(background, texture, sfFalse);
    sfSprite_setScale(background, w_prop->scale);
    return (background);
}

sfSprite *set_background(int wi, int he, win_prop *w_prop)
{
    sfSprite *background = sfSprite_create();
    sfTexture *texture = sfTexture_create(wi, he);

    texture = sfTexture_createFromFile("sprites/stage.png", NULL);
    sfTexture_updateFromPixels(texture, w_prop->fb->pixels, wi, he, 400, 400);
    sfSprite_setTexture(background, texture, sfFalse);
    sfSprite_setScale(background, w_prop->scale);
    return (background);
}

sfSprite *set_fond(int wi, int he, win_prop *w_prop)
{
    sfSprite *background = sfSprite_create();
    sfTexture *texture = sfTexture_create(wi, he);

    texture = sfTexture_createFromFile("sprites/fond.png", NULL);
    sfTexture_updateFromPixels(texture, w_prop->fb->pixels, wi, he, 400, 400);
    sfSprite_setTexture(background, texture, sfFalse);
    sfSprite_setScale(background, w_prop->scale);
    return (background);
}

sfSprite *set_background_main_menu(win_prop *w_prop)
{
    int wi = w_prop->width;
    int he = w_prop->height;
    sfSprite *background = sfSprite_create();
    sfTexture *texture = sfTexture_create(wi, he);

    texture = sfTexture_createFromFile("sprites/fond_main_menu.png", NULL);
    sfTexture_updateFromPixels(texture, w_prop->fb->pixels, wi, he, 400, 400);
    sfSprite_setTexture(background, texture, sfFalse);
    sfSprite_setScale(background, w_prop->scale);
    return (background);
}
