/*
** EPITECH PROJECT, 2019
** actions_and_events_keys.c
** File description:
** actions and events keyboard
*/

#include "bonus.h"

void turn_car(window_t *b, ai_t *w, float nb)
{
    float dir = w->wheels_dir + nb;

    if (nb > 0 && w->wheels_dir < -0.0001)
        dir = 0.0001;
    if (nb < 0 && w->wheels_dir > 0.0001)
        dir = -0.0001;
    if (w->wheels_dir + nb >= -1 && w->wheels_dir + nb <= 1)
        if (wheels_dir(w, dir) != 0)
            exit(1);
    reset_time(b->stop->time_anim, b->clock);
}

int move_forward_car(window_t *b, ai_t *w, float nb)
{
    if (w->b_speed > 0) {
        car_forward(w, 0.001);
        return (0);
    }
    if (w->f_speed + nb >= 0 && w->f_speed + nb <= 1)
        if (car_forward(w, w->f_speed + nb) != 0)
            exit(1);
    reset_time(b->stop->time_anim, b->clock);
    return (0);
}

int move_backwards_car(window_t *b, ai_t *w, float nb)
{
    if (w->f_speed > 0) {
        car_backwards(w, 0.001);
        return (0);
    }
    if (w->b_speed + nb >= 0 && w->b_speed + nb <= 1)
        if (car_backwards(w, w->b_speed + nb) != 0)
            exit(1);
    reset_time(b->stop->time_anim, b->clock);
    return (0);
}

void actions_and_events_keys(window_t *b, ai_t *w)
{
    if (KEY_R(sfKeyD) || KEY_R(sfKeyRight)) {
        turn_car(b, w, -0.1);
    }
    if (KEY_R(sfKeyQ) || KEY_R(sfKeyLeft)) {
        turn_car(b, w, 0.1);
    }
    if (KEY_R(sfKeyZ) || KEY_R(sfKeyUp)) {
        move_forward_car(b, w, 0.1);
    }
    if (KEY_R(sfKeyS) || KEY_R(sfKeyDown)) {
        move_backwards_car(b, w, 0.1);
    }
    if (KEY_R(sfKeySpace)) {
        move_forward_car(b, w, -(w->f_speed));
        turn_car(b, w, -(w->wheels_dir));
    }
}
