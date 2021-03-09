/*
** EPITECH PROJECT, 2019
** detect_end.c
** File description:
** detect_end
*/

#include "my.h"

int is_distance(char *line)
{
    int nb_sep = 0;

    for (int i = 0; line[i] != 0; i++)
        if (line[i] == ':')
            nb_sep++;
    if (nb_sep >= 32)
        return (1);
    return (0);
}

int detect_end(char *line, ai_t *w)
{
    char *part = NULL;

    if (line == NULL || line[0] == 0)
        exit(84);
    part = get_track(line);
    if (is_distance(line) == 1) {
        put_distance(line, w);
        detect_collision_wheel(w, w->f_speed, w->b_speed);
    }
    if (my_strcmp("Track Cleared", part) == 1) {
        my_putstr("stop_simulation\n");
        free(part);
        return (1);
    }
    free(part);
    return (0);
}
