/*
** EPITECH PROJECT, 2018
** duck.c
** File description:
** duck movement
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

duck_prop set_duck_props(duck_prop duck, win_prop *w_prop)
{
    duck.sprite = set_duck(w_prop->width, w_prop->height, w_prop);
    duck.position.x = 300;
    duck.position.y = 400;
    duck.rect.left = 0;
    duck.rect.top = 0;
    duck.rect.width = 110;
    duck.rect.height = 110;
    duck.speed = 1;
    duck.sens_h = 1;
    duck.sens_v = 0;
    duck.clock_anim = sfClock_create();
    duck.clock_mov = sfClock_create();
    return (duck);
}

sfVector2f duck_movements2(duck_prop *dk, win_prop *w_prop)
{
    if (dk->position.x / w_prop->scale_x < -100)
        dk->position.x = 815;
    if (dk->position.y / w_prop->scale_y >= 530) {
        dk->position.y -= 5;
        dk->sens_v = 2;
    }
    if (dk->position.y / w_prop->scale_y <= -25) {
        dk->position.y += 5;
        dk->sens_v = 1;
    }
    return (dk->position);
}

sfVector2f duck_movements(duck_prop *dk, win_prop *w_prop)
{
    sfTime times = sfClock_getElapsedTime(dk->clock_mov);
    float time = times.microseconds / 1000000.0 * 35.0;

    dk->position.x += 12 * dk->sens_h * w_prop->scale_x * dk->speed * time;
    if (dk->sens_v == 1)
        dk->position.y += (3 * w_prop->scale_y * dk->speed * time);
    if (dk->sens_v == 2)
        dk->position.y -= (3 * w_prop->scale_y * dk->speed * time);
    if (dk->position.x / w_prop->scale_x >= 815) {
        dk->position.x = -100;
        dk->sens_v = rand() % 3;
    }
    dk->position = duck_movements2(dk, w_prop);
    sfClock_restart(dk->clock_mov);
    return (dk->position);
}
