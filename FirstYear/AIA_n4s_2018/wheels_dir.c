/*
** EPITECH PROJECT, 2019
** wheels_dir.c
** File description:
** wheels_dir.c
*/

#include "my.h"

int cycle_wait(ai_t *w)
{
    char *line;
    int err;

    my_putstr("cycle_wait:1\n");
    line = get_next_line(0);
    err = detect_end(line, w);
    return (err);
}

int wheels_dir(ai_t *w, float value)
{
    char *line;
    int err;

    if (value != w->wheels_dir) {
        sprintf(w->opt, "%0.2f", value);
        my_putstr("wheels_dir:");
        my_putstr(w->opt);
        my_putstr("\n");
        w->wheels_dir = value;
        line = get_next_line(0);
        err = detect_end(line, w);
    }
    return (err);
}

int car_forward(ai_t *w, float value)
{
    char *line;
    int err;

    if (value != w->f_speed) {
        sprintf(w->opt, "%0.2f", value);
        my_putstr("car_forward:");
        my_putstr(w->opt);
        my_putstr("\n");
        w->f_speed = value;
        w->b_speed = 0;
        line = get_next_line(0);
        err = detect_end(line, w);
    }
    return (err);
}

int car_backwards(ai_t *w, float value)
{
    char *line;
    int err;

    if (value != w->b_speed) {
        sprintf(w->opt, "%0.2f", value);
        my_putstr("car_backwards:");
        my_putstr(w->opt);
        my_putstr("\n");
        w->b_speed = value;
        w->f_speed = 0;
        line = get_next_line(0);
        err = detect_end(line, w);
    }
    return (err);
}
