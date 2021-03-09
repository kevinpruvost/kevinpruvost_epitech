/*
** EPITECH PROJECT, 2019
** redirected_calculate.c
** File description:
** redirected calculate
*/

#include "my.h"

float right_calculate(ai_t *w)
{
    float right = 0;

    for (int i = 16; i < 28; i++) {
        (w->res[i] != 84) ? (right += w->res[i]) : (0);
    }
    for (int i = 28; i < 32; i++) {
        (w->res[i] != 84) ? (right += w->res[i]) : (0);
    }
    right /= 16;
    return (right);
}

float left_calculate(ai_t *w)
{
    float left = 0;

    for (int i = 0; i < 4; i++)
        (w->res[i] != 84) ? (left += w->res[i]) : (0);
    for (int i = 4; i < 16; i++)
        (w->res[i] != 84) ? (left += w->res[i]) : (0);
    left /= 16;
    return (left);
}
