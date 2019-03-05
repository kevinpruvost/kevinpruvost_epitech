/*
** EPITECH PROJECT, 2018
** shooting_system.c
** File description:
** shots
*/

#include "include/my.h"
#include <stdlib.h>
#include <math.h>

sfVector2f spawn_alea(sfVector2f positionDuck, int *direction)
{
    if (rand() % 2 == 1) {
        positionDuck.x = -100;
        *direction = 1;
    } else {
        positionDuck.x = 815;
        *direction = -1;
    }
    return (positionDuck);
}

void render_ammo(win_prop *w_prop, game_info *game_infos)
{
    sfSprite *ammo = sfSprite_create();
    sfTexture *texture = sfTexture_create(w_prop->width, w_prop->height);
    sfVector2f pos = {620 * w_prop->scale_x, 680 * w_prop->scale_y};
    int wi = w_prop->width;
    int he = w_prop->height;

    if (game_infos->AMMO == 3)
        texture = sfTexture_createFromFile("sprites/ammo_3.png", NULL);
    if (game_infos->AMMO == 2)
        texture = sfTexture_createFromFile("sprites/ammo_2.png", NULL);
    if (game_infos->AMMO == 1)
        texture = sfTexture_createFromFile("sprites/ammo_1.png", NULL);
    sfTexture_updateFromPixels(texture, w_prop->fb->pixels, wi, he, 400, 400);
    sfSprite_setTexture(ammo, texture, sfFalse);
    sfSprite_setScale(ammo, w_prop->scale);
    sfSprite_setPosition(ammo, pos);
    sfRenderWindow_drawSprite(w_prop->window, ammo, NULL);
}

void shooting_sound(sfSound *sound, sfClock *clock)
{
    sfTime time = sfClock_getElapsedTime(clock);
    float seconds = time.microseconds / 1000000.0;

    if (seconds >= 0.5)
        sfSound_play(sound);
}

int in_duck(cross_prop cr, duck_prop *dk, int ecx, int ecy)
{
    int in = 0;
    float dkx = dk->position.x;
    float dky = dk->position.y;
    float crx = cr.position.x;
    float cry = cr.position.y;

    if (dkx >= crx - ecx && dkx <= crx + ecx)
        if (dky >= cry - ecy && dky <= cry + ecy)
            in = 1;
    return (in);
}

sfVector2f shoot(cross_prop cr, win_prop *w_prop, game_info *gm, duck_prop *dk)
{
    sfMouseButton mbutton;
    int ecx = 50 * w_prop->scale_x;
    int ecy = 50 * w_prop->scale_y;
    sfTime time = sfClock_getElapsedTime(cr.clock);
    float seconds = time.microseconds / 1000000.0;

    if (seconds < 0.5)
        return (dk->position);
    sfSound_play(cr.sound);
    if (in_duck(cr, dk, ecx, ecy) == 1) {
        dk->sens_v = rand() % 3, gm->score = gm->score + 1;
        dk->position.y = rand() % (int)(500 * w_prop->scale_y);
        dk->position.x = (int)(-100 * w_prop->scale_x);
        gm->AMMO = 4, dk->speed = dk->speed + 0.05;
    }
    gm->AMMO -= 1;
    sfClock_restart(cr.clock);
    return (dk->position);
}
