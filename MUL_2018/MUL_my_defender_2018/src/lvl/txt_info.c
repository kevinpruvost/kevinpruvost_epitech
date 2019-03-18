/*
** EPITECH PROJECT, 2019
** txt_info.c
** File description:
** funcs related to txt
*/

#include "my.h"

void actualize_txt(game_s *game)
{
    sfText_setString
    (game->lvl_vars->player->hp_txt->text,
    str_add("HP :      ", my_getnbr(game->lvl_vars->player->hp)));
    sfText_setString(game->lvl_vars->player->wave_txt->text,
    str_add("Wave :  ", my_getnbr(game->lvl_vars->player->wave)));
    sfText_setString(game->lvl_vars->player->money_txt->text,
    str_add("Money : ", my_getnbr(game->lvl_vars->player->money)));
}
