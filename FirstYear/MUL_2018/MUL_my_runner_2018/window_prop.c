/*
** EPITECH PROJECT, 2018
** window_prop.c
** File description:
** window_prop functions
*/

#include "include/my.h"

w_prop *create_win_prop(int wid, int hei, float ips)
{
    w_prop *win = malloc(sizeof(w_prop));
    char *n = "Shrekometry Dash";

    win->width = wid;
    win->height = hei;
    win->fps = ips;
    win->scale.x = wid / 800.0;
    win->scale.y = hei / 800.0;
    win->mode.width = wid;
    win->mode.height = hei;
    win->mode.bitsPerPixel = 32;
    win->win = sfRenderWindow_create(win->mode, n, sfResize | sfClose, NULL);
    win->fb = framebuffer_create(wid, hei);
    win->music = music_create();
    return (win);
}

void destroy_win_prop(w_prop *window)
{
    if (sfRenderWindow_isOpen(window->win) == 1)
        sfRenderWindow_close(window->win);
    sfRenderWindow_destroy(window->win);
    if (sfMusic_getStatus(window->music) == sfPlaying)
        sfMusic_stop(window->music);
    sfMusic_destroy(window->music);
    free(window);
}
