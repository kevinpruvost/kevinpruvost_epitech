/*
** EPITECH PROJECT, 2019
** window_check.c
** File description:
** window check funcs
*/

#include "my.h"

void window_check(sfRenderWindow *win)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(win, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(win);
    }
}
