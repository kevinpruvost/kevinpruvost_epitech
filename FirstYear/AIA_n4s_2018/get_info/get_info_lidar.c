/*
** EPITECH PROJECT, 2019
** get_info_lidar.c
** File description:
** get info lidar
*/

#include "my.h"

void convert_put_distance(char *nb, ai_t *w, int nb_sep)
{
    w->dist[nb_sep] = atof(nb);
    for (int i = 0; i < 10; i++)
        nb[i] = 0;
}

void put_distance(char *line, ai_t *w)
{
    int nb_sep = 0;
    char *nb = create_string(10);

    w->launch = 1;
    for (int i = 0, j = 0; line[i] != 0 && nb_sep <= 32 + 3; i++) {
        if (line[i] == ':' && nb_sep >= 3) {
            convert_put_distance(nb, w, nb_sep - 3);
        }
        if (line[i] == ':') {
            nb_sep++;
            j = 0;
        }
        if (nb_sep >= 3 && line[i] != ':') {
            nb[j] = line[i];
            j++;
        }
    }
    free(nb);
}

int get_info_lidar(ai_t *w)
{
    char *line;
    int err = 0;

    my_putstr("get_info_lidar\n");
    line = get_next_line(0);
    err = detect_end(line, w);
    return (err);
}
