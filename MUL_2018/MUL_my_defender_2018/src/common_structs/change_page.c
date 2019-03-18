/*
** EPITECH PROJECT, 2019
** change_page.c
** File description:
** change pages funcs
*/

#include "my.h"

void change_page(game_s *game, int page)
{
    game->old_page = game->page;
    game->page = page;
}

void change_page_back(game_s *game)
{
    page_t mem = game->page;

    game->page = game->old_page;
    game->old_page = mem;
}
