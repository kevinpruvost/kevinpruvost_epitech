/*
** EPITECH PROJECT, 2019
** generate_random_map.c
** File description:
** function to create random map
*/

#include "my.h"

void change_value(map_t *map, int x, int y, int order)
{
    map->orders[order]->x = x;
    map->orders[order]->y = y;
    map->orders[order]->order = order;
    map->map_id[x][y] = 1;
    change_map_1(map->map_case[x][y]);
}

sim_map_t *create_sim_grm(void)
{
    sim_map_t *sim = malloc(sizeof(sim_map_t));

    sim->x = 0;
    sim->y = 0;
    sim->sens_x = 1;
    sim->sens_y = 1;
    sim->done = 0;
    sim->order = 2;
    return (sim);
}

void generate_random_map2(sim_map_t *sim, map_t *map)
{
    (sim->sens_x == 0) ? (sim->sens_x = -1) : (0);
    (sim->sens_y == 0) ? (sim->sens_y = -1) : (0);
    (sim->y + sim->sens_y > 5 || sim->y + sim->sens_y < 0)
        ? (sim->sens_y = 0) : (0);
    (sim->x + sim->sens_x > 9 || sim->x + sim->sens_x < 0)
        ? (sim->sens_x = 0) : (0);
    if (map->map_id[sim->x][sim->y+sim->sens_y] == 0 &&
        possible_way(map, sim->x, sim->y + sim->sens_y) == 0) {
        sim->y += sim->sens_y;
        change_value(map, sim->x, sim->y, sim->order);
        sim->order += 1;
        sim->done = 1;
    } else if (map->map_id[sim->x+sim->sens_x][sim->y] == 0 &&
        possible_way(map, sim->x + sim->sens_x, sim->y) == 0) {
        sim->x += sim->sens_x;
        change_value(map, sim->x, sim->y, sim->order);
        sim->order += 1;
        sim->done = 1;
    }
}

void generate_random_map(map_t *map)
{
    sim_map_t *sim = create_sim_grm();

    sim->x = rand() % 10;
    change_value(map, sim->x, sim->y, 1);
    for (; sim->y != 5 || sim->x != 4; sim->done = 0) {
        while (sim->done == 0) {
            sim->sens_x = rand() % 2;
            sim->sens_y = rand() % 2;
            generate_random_map2(sim, map);
        }
    }
    map_spriting(map);
}

void regenerate_random_map(map_t *map)
{
    clear_map(map);
    generate_random_map(map);
}
