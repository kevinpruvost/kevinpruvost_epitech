/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "drawing.h"
#include "bitmap.h"

#include <stdio.h>
#include <stdlib.h>

void set_menger1(coord_t *p, int s)
{
    p->x -= s;
    p->y -= s;
    p->s = s;
}

void set_menger2(coord_t *p, int s, int x, int y)
{
    p->x = (x*s)+(s/3) + p->x;
    p->y = (y*s)+(s/3) + p->y;
}

void set_menger3(coord_t *p, int s, int x, int y)
{
    p->x = p->x - ((x*s)+(s/3));
    p->y = p->y - ((y*s)+(s/3));
}

void menger(coord_t p, int level, unsigned int **img)
{
    int s = p.s/3;

    if (level == 0)
        return;
    if (p.s >= 3)
        menger_draw(p, img, level);
    if (level < 2 || p.s < 3)
        return;
    set_menger1(&p, s);
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            if (x == 1 && y == 1)
                continue;
            set_menger2(&p, s, x, y);
            menger(p, (level - 1), img);
            set_menger3(&p, s, x, y);
        }
    }
}