/*
** EPITECH PROJECT, 2019
** vars2.c
** File description:
** for map_vars
*/

#include "my.h"

map_vars *map_vars_create2(char **map_c)
{
    map_vars *map = malloc(sizeof(map_vars));

    map->map_char = map_c;
    for (int i = 0; map_c[i] != NULL; i++)
        map->height += 1;
    for (int i = 0; map_c[0][i] != 0; i++)
        map->width += 1;
    map->blocks = malloc(sizeof(gm_vars *) * (map->height + 1));
    map->id_blocks = malloc(sizeof(int *) * (map->height + 1));
    return (map);
}

map_vars *map_vars_create(char **map_c, sfVector2f scale)
{
    map_vars *map = map_vars_create2(map_c);

    for (int i = 0; i < map->height; i++) {
        map->blocks[i] = malloc(sizeof(gm_vars) * (map->width + 1));
        map->id_blocks[i] = malloc(sizeof(int) * (map->width + 1));
        for (int j = 0; j < map->width; j++) {
            if (i == 9) {
                map->id_blocks[i][j] = 1;
                map->blocks[i][j] = create_block(1, scale, i, j);
            } else if (map_c[i][j] != '1' && map_c[i][j] != '2'
            && map_c[i][j] != '3') {
                map->id_blocks[i][j] = 4;
                map->blocks[i][j] = create_block(4, scale, i, j);
            } else {
                map->id_blocks[i][j] = map_c[i][j] - 48;
                map->blocks[i][j] = create_block(map_c[i][j] - 48, scale, i, j);
            }
        }
    }
    return (map);
}
