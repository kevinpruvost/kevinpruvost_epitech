/*
** EPITECH PROJECT, 2019
** ai.c
** File description:
** ai funcs
*/

#include "my.h"

int ai(ai_t *w)
{
    char *line = NULL;
    float forward = detect_collision_front(w);
    float backwards = detect_collision_back(w);
    float wheel = detect_collision_wheel(w, forward, backwards);
    int err;

    print_dist(w);
    if (forward > 0.5)
        wheel = 0;
    if (backwards != 0) {
        wheel *= -1;
        car_backwards(w, backwards);
    } else
        car_forward(w, forward);
    wheels_dir(w, wheel);
    redirected(w);
    return (err);
}
