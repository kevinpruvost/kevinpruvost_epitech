/*
** EPITECH PROJECT, 2019
** end_game.c
** File description:
** to end the game funcs
*/

#include "my.h"

void end_back(game_s *game)
{
    destroy_lvl_s(game->lvl_vars);
    game->lvl_vars = create_lvl_s(game->clock);
    change_page_back(game);
}

void end_main_menu(game_s *game)
{
    destroy_lvl_s(game->lvl_vars);
    game->lvl_vars = create_lvl_s(game->clock);
    change_page(game, MAINMENU);
}

void end_game(game_s *game)
{
    if (game->lvl_vars->player->hp <= 0) {
        game->score = game->lvl_vars->player->wave;
        end_main_menu(game);
        add_new_score(game);
        actualize_score(game);
    }
}
