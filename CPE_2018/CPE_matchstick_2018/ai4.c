/*
** EPITECH PROJECT, 2019
** ai4.c
** File description:
** ai funcs
*/

#include "my.h"

void random_choice(match_t *m, int *line_ask, int *matches_ask)
{
    while (*line_ask <= 0 || m->matches_nb[*line_ask] <= 0) {
        *line_ask = random() % (m->lines + 1);
    }
    if (m->matches_nb[*line_ask] >= m->max_remove) {
        while (*matches_ask <= 0 || *matches_ask > m->max_remove)
            *matches_ask = random() % (m->max_remove + 1);
    } else {
        while (*matches_ask <= 0 || *matches_ask > m->matches_nb[*line_ask])
            *matches_ask = random() % (m->matches_nb[*line_ask] + 1);
    }
}
