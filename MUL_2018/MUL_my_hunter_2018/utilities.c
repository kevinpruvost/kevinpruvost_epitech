/*
** EPITECH PROJECT, 2018
** utilities.c
** File description:
** usable functions for csfml
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

void music_launching(sounds *sounds_prop)
{
    if (sfMusic_getStatus(sounds_prop->music) != sfPlaying) {
        sfMusic_setVolume(sounds_prop->music, 5);
        sfMusic_play(sounds_prop->music);
    }
}

void move_rect(sfIntRect *rect, int offset, int max_value)
{
    if (rect->left >= max_value - offset)
        rect->left = 0;
    else
        rect->left = rect->left + offset;
}

int is_timepassed(sfClock *clock, float seconds_tocheck)
{
    sfTime time = sfClock_getElapsedTime(clock);
    float seconds = time.microseconds / 1000000.0;
    float mult = 0.00;
    int mult_int = 0;

    if (seconds == seconds_tocheck)
        return (1);
    mult = seconds / seconds_tocheck;
    mult_int = (int)(mult);
    if (mult >= 1) {
        sfClock_restart(clock);
        return (1);
    }
    return (0);
}

void timer(float seconds_towait)
{
    sfClock *clock = sfClock_create();
    sfTime time;
    float seconds;
    int done = 0;

    while (done == 0) {
        time = sfClock_getElapsedTime(clock);
        seconds = time.microseconds / 1000000.0;
        if (seconds >= seconds_towait) {
            done = 1;
            sfClock_restart(clock);
        }
    }
}

void clear_framebuffer(int width, int height, framebuffer_t *fb)
{
    for (int i = 1; i <= width; i++) {
        for (int j = 1; j <= height; j++) {
            put_pixel(i, j, sfTransparent, fb);
        }
    }
}
