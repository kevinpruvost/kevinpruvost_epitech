/*
** EPITECH PROJECT, 2019
** detect_collision.c
** File description:
** detect collisions
*/

#include "my.h"

float detect_collision_front(ai_t *w)
{
    float value = 0.72;

    for (int i = 9; i < 22; i++) {
        if (i >= 13 && i <= 17)
            (w->dist[i] < 1000) ? (value = 0.55) : (0);
        (w->dist[i] < 400) ? (value = 0.195) : (0);
        (w->dist[i] < 200) ? (value = 0.1) : (0);
    }
    return (value);
}

float detect_collision_back(ai_t *w)
{
    for (int i = 0; i < 32; i++) {
        if (w->dist[i] < 100)
            return (0.5);
    }
    return (0);
}

double detect_right(ai_t *w, float f, float b)
{
    double value_right = 0;
    double buff = 0;

    for (int i = 15; i < 31; i++) {
        buff = mult_parallel(w->dist[i], w->dist[i+1], 1.875,
        (i - 15) * 1.875);
        (buff == 84) ? (w->res[i] = 84) : (w->res[i] = buff);
        (isnan(w->res[i]) != 0) ? (w->res[i] = 84) : (0);
    }
    return (value_right);
}

double detect_left(ai_t *w, float f, float b)
{
    double value_left = 0;
    double buff = 0;

    for (int i = 0; i < 15; i++) {
        buff = mult_parallel(w->dist[i+1], w->dist[i], 1.875,
        30 - 1.875 * (i + 1));
        (buff == 84) ? (w->res[i] = 84) : (w->res[i] = buff * (-1));
        (isnan(w->res[i]) != 0) ? (w->res[i] = 84) : (0);
    }
    return (value_left);
}

float detect_collision_wheel(ai_t *w, float f, float b)
{
    double value = 0;
    double value_left = detect_left(w, f, b);
    double value_right = detect_right(w, f, b);

    return (value);
}
