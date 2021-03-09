/*
** EPITECH PROJECT, 2019
** print_dist.c
** File description:
** print dist
*/

#include "my.h"

void print_dist2(ai_t *w, char *line)
{
    double coeff = 1.0 / 2.0;
    double values[3] = {0.0, 0.0, coeff / 32.0};
    double value = 0;

    my_putstr_error_n("[");
    for (int i = 0; i < 16; i++, coeff -= values[2])
        value += (1 / w->dist[i] * coeff);
    sprintf(line, "%.4f", value);
    my_putstr_error_n(line);
    value = 0;
    for (int i = 16; i < 32; i++, coeff += values[2])
        value += (1 / w->dist[i] * coeff);
    sprintf(line, "%.4f", value);
    my_putstr_error_n(", ");
    my_putstr_error_n(line);
    my_putstr_error_n("]\n");
}

int print_dist(ai_t *w)
{
    char *line = create_string(10);
    static int ct = 0;

    ct++;
    if (ct % 6 != 0)
        return (0);
    print_dist2(w, line);
    free(line);
}
