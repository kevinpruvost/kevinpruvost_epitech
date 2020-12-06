/*
** EPITECH PROJECT, 2019
** build_map.c
** File description:
** funcs to build map
*/

#include "my.h"

void add_case(game_s *game, int x, int y)
{
    int n = 1;
    map_t *map = game->map;

    for (n = 1; map->orders[n]->order == n; n++);
    game->map->orders[n]->x = x;
    game->map->orders[n]->y = y;
    game->map->orders[n]->order = n;
    game->map->map_id[x][y] = 1;
    change_map_1(game->map->map_case[x][y]);
    if (x == 4 && y == 5) {
        map_spriting(map);
    }
}

void show_p_cases_3(game_s *game, int x, int y, sfColor color)
{
    if (y != 5 && possible_way(game->map, x, y+1) == 0
        && game->map->map_id[x][y+1] == 0)
        sfSprite_setColor(game->maped_vars->p_cases[x][y+1]->sprite, color);
    if (y != 0 && possible_way(game->map, x, y-1) == 0
        && game->map->map_id[x][y-1] == 0)
        sfSprite_setColor(game->maped_vars->p_cases[x][y-1]->sprite, color);
}

void show_p_cases_2(game_s *game, int lb)
{
    sfColor color = {0, 255, 0, 120};
    int x = game->map->orders[lb]->x;
    int y = game->map->orders[lb]->y;

    if (x != 9 && possible_way(game->map, x+1, y) == 0
        && game->map->map_id[x+1][y] == 0)
        sfSprite_setColor(game->maped_vars->p_cases[x+1][y]->sprite, color);
    if (x != 0 && possible_way(game->map, x-1, y) == 0
        && game->map->map_id[x-1][y] == 0)
        sfSprite_setColor(game->maped_vars->p_cases[x-1][y]->sprite, color);
    show_p_cases_3(game, x, y, color);
}

void show_p_cases(game_s *game)
{
    int lb = 1;
    map_t *map = game->map;
    sfColor clear = {0, 0, 0, 0};
    sfColor color = {0, 255, 0, 120};

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 6; j++)
            sfSprite_setColor(game->maped_vars->p_cases[i][j]->sprite, clear);
    for (lb = 1; map->orders[lb]->order == lb; lb++);
    if (lb == 1) {
        for (int i = 0; i < 10; i++)
            sfSprite_setColor(game->maped_vars->p_cases[i][0]->sprite, color);
    } else if (map->orders[lb-1]->x != 4 || map->orders[lb-1]->y != 5)
            show_p_cases_2(game, lb - 1);
}
