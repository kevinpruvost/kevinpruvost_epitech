/*
** EPITECH PROJECT, 2019
** generate_random_map2.c
** File description:
** following of generate random map
*/

#include "my.h"

int **map_id_test_create(map_t *map, int x, int y)
{
    int **map_id_test = malloc(sizeof(int *) * 10);

    for (int i = 0; i < 10; i++) {
        map_id_test[i] = malloc(sizeof(int) * 10);
        for (int j = 0; j < 6; j++)
            map_id_test[i][j] = map->map_id[i][j];
    }
    map_id_test[x][y] = 1;
    return (map_id_test);
}

sim_map_t *sim_map_create(map_t *map, int x, int y)
{
    sim_map_t *sim = malloc(sizeof(sim_map_t));

    sim->x_test = x;
    sim->y_test = y;
    sim->map_id_test = map_id_test_create(map, x, y);
    sim->sens_x = 1;
    sim->sens_y = 1;
    sim->n = 1;
    return (sim);
}

void possible_way2(sim_map_t *sim)
{
    sim->sens_x = rand() % 2;
    sim->sens_y = rand() % 2;
    (sim->sens_x == 0) ? (sim->sens_x = -1) : (0);
    (sim->sens_y == 0) ? (sim->sens_y = -1) : (0);
    if (sim->x_test + sim->sens_x < 10 && sim->x_test + sim->sens_x >= 0
        && sim->map_id_test[sim->x_test + sim->sens_x][sim->y_test] == 0) {
        sim->x_test += sim->sens_x;
        sim->map_id_test[sim->x_test][sim->y_test] = 61;
    }
    if (sim->y_test + sim->sens_y < 6 && sim->y_test + sim->sens_y >= 0
        && sim->map_id_test[sim->x_test][sim->y_test + sim->sens_y] == 0) {
        sim->y_test += sim->sens_y;
        sim->map_id_test[sim->x_test][sim->y_test] = 61;
    }
    if (sim->x_test == 4 && sim->y_test == 5)
        sim->n = 0;
}

int possible_way(map_t *map, int x, int y)
{
    sim_map_t *sim = sim_map_create(map, x, y);
    int n = 0;

    if (x == 4 && y == 5)
        return (0);
    for (int e = 1; e < 500 && sim->n == 1; e++) {
        if (stuck(sim->map_id_test, sim->x_test, sim->y_test) == 1) {
            sim->map_id_test[sim->x_test][sim->y_test] = 1;
            sim->map_id_test = map_id_replace(sim->map_id_test);
            sim->x_test = x;
            sim->y_test = y;
        }
        possible_way2(sim);
    }
    for (int i = 9; i >= 0; i--)
        free(sim->map_id_test[i]);
    free(sim->map_id_test);
    n = sim->n;
    free(sim);
    return (n);
}
