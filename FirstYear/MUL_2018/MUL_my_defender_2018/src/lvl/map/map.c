/*
** EPITECH PROJECT, 2019
** map.c
** File description:
** create and destroy map
*/

#include "my.h"

void change_map_empty(game_obj *map_case)
{
    map_case->texture = sfTexture_createFromFile
        ("assets/sprites/chemin_vide.png", NULL);
    sfSprite_setTexture(map_case->sprite, map_case->texture, sfTrue);
}

void change_map_1(game_obj *map_case)
{
    map_case->texture = sfTexture_createFromFile
        ("assets/sprites/chemin1.png", NULL);
    sfSprite_setTexture(map_case->sprite, map_case->texture, sfTrue);
}

map_t *create_map2(map_t *map)
{
    map->change_case[0] = change_map_empty;
    map->change_case[1] = change_map_1;
    map->change_case[2] = change_map_2;
    map->change_case[3] = change_map_3;
    map->change_case[4] = change_map_4;
    map->change_case[5] = change_map_5;
    map->change_case[6] = change_map_6;
    map->orders = malloc(sizeof(order_t) * (10 + 1) * (6 + 1));
    for (int i = 0; i < (10 + 1) * (6 + 1); i++) {
        map->orders[i] = malloc(sizeof(order_t));
        map->orders[i]->order = -1;
        map->orders[i]->x = -1;
        map->orders[i]->y = -1;
    }
    return (map);
}

map_t *create_map(sfClock *clock)
{
    map_t *map = malloc(sizeof(map_t));
    sfIntRect rect = {0, 0, 100, 100};
    sfVector2f pos = {0, 0};

    for (int i = 0; i < 10 + 1; i++) {
        for (int j = 0; j < 6 + 1; j++) {
            map->map_id[i][j] = 0;
            map->map_case[i][j] = create_game_obj
                ("assets/sprites/chemin_vide.png", rect, pos, clock);
            pos.y += 100;
        }
        pos.x += 100;
        pos.y = 0;
    }
    map = create_map2(map);
    clear_map(map);
    generate_random_map(map);
    return (map);
}

void destroy_map(map_t *map)
{
    for (int i = 10; i >= 0; i--) {
        for (int j = 6; j >= 0; j--) {
            destroy_game_obj(map->map_case[i][j]);
        }
    }
    for (int i = (10 + 1) * (6 + 1) - 1; i >= 0; i--)
        free(map->orders[i]);
    free(map->orders);
    free(map);
}
