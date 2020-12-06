/*
** EPITECH PROJECT, 2019
** create_grid.c
** File description:
** create grid
*/

#include "my.h"

bgd_obj *create_grid(void)
{
    bgd_obj *grid;
    sfIntRect rect = {0, 0, 1000, 601};
    sfVector2f scale = {1, 1};

    grid = create_bgd_obj("assets/sprites/grid.png", rect, scale);
    return (grid);
}
