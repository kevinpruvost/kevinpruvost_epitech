/*
** EPITECH PROJECT, 2019
** destroy.c
** File description:
** destroy everything
*/

#include "my.h"

void destroy(game_s *game, funcs_game_t *funcs)
{
    destroy_game_s(game);
    free(funcs);
}
