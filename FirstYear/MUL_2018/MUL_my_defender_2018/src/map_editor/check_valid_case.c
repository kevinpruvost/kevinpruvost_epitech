/*
** EPITECH PROJECT, 2019
** check_valid_case.c
** File description:
** if case is green
*/

#include "my.h"

int check_valid_case(game_obj *cases)
{
    sfColor color = sfSprite_getColor(cases->sprite);

    if (color.g == 255)
        return (1);
    return (0);
}
