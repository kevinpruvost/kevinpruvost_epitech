/*
** EPITECH PROJECT, 2019
** create_ai.c
** File description:
** create ai
*/

#include "my.h"

void srand_set(void)
{
    srand(time(NULL));
}

ai_t *create_ai_t(void)
{
    ai_t *w = malloc(sizeof(ai_t));

    srand_set();
    for (int i = 0; i < 32; i++) {
        w->dist[i] = 0;
        w->res[i] = 0;
    }
    w->order = NULL;
    w->opt = create_string(10);
    w->wheels_dir = 0;
    w->f_speed = 0.5;
    w->b_speed = 0;
    w->launch = 0;
    return (w);
}

void destroy_ai_t(ai_t *w)
{
    free(w->opt);
    free(w);
}
