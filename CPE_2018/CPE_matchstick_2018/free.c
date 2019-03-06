/*
** EPITECH PROJECT, 2019
** free.c
** File description:
** to free func
*/

#include "my.h"

void free_m(match_t *m)
{
    free(m->matches_nb);
    for (int i = 0; i < m->lines + 2; i++)
        free(m->arr[i]);
    free(m->arr);
    free(m->lines_id);
    free(m->pairs);
    for (int i = 0; i < m->lines * 2 + 1; i++)
        free(m->pairs_lines[i]);
    free(m->pairs_lines);
    free(m);
}
