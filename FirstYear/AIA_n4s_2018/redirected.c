/*
** EPITECH PROJECT, 2019
** redirect
** File description:
** redirect
*/

#include "my.h"

float go_backward(ai_t *w, float right, float left)
{
    float direction = 0;
    float buff = right;

    if (right >= left) {
        right = (left - right) * -1 * 0.2;
        left = (buff - left) * -1 * 0.2;
    } else {
        right = (right - left) * -1 * 0.2;
        left = (buff - right) * -1 * 0.2;
    }
    (direction == 1) ? (direction = right) : (direction = left);
    for (int i = 0; i < 32; i++) {
        if (w->dist[i] <= 100 && w->dist[i] != 0) {
            car_backwards(w, 1);
            wheels_dir(w, direction);
        }
    }
    return 0;
}

float go_right(ai_t *w, float right, float left)
{
    if (right >= left)
        right = left - right;
    else
        right = right - left;
    dprintf(2, "go right %f\n", right);
    if (right < -1)
        right = -1;
    if (right == 84)
        return 0;
    car_forward(w, detect_collision_front(w));
    wheels_dir(w, right * 0.5);
    return 0;
}

float go_left(ai_t *w, float right, float left)
{
    if (left <= right)
        left = right - left;
    else
        left = left - right;
    dprintf(2, "go left %f\n", left);
    if (left > 1)
        left = 1;
    if (left == 84)
        return 0;
    car_forward(w, detect_collision_front(w));
    wheels_dir(w, left * 0.5);
    return 0;
}

int back_need(ai_t *w)
{
    int compteur = 0;

    for (int i = 0; i < 31; i++) {
        if (w->dist[i] <= 100)
            compteur++;
        if (compteur >= 2)
            return (-1);
    }
    return (1);
}

void redirected(ai_t *w)
{
    float angle[2] = {0, 0};
    float right = right_calculate(w);
    float left = left_calculate(w);
    int back = back_need(w);

    if (back == -1) {
        angle[0] = go_backward(w, right, left);
    } else
        car_forward(w, 1);
    if (left > -right && back != -1) {
        angle[0] = go_left(w, right, left);
    } else if (-right > left && back != -1)
        angle[0] = go_right(w, right, left);
    if (!(w->dist[0] <= 150 && w->dist[1] <= 150 &&
        w->dist[30] <= 150 && w->dist[31] <= 150)) {
        (w->dist[0] <= 150 || w->dist[1] <= 150) ?
        (wheels_dir(w, -0.2 * back)) : (0);
        (w->dist[30] <= 150 || w->dist[31] <= 150)
        ? (wheels_dir(w, 0.2 * back)) : (0);
    }
}
