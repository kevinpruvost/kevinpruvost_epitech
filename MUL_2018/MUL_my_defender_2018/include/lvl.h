/*
** EPITECH PROJECT, 2019
** lvl;h
** File description:
** lvl funcs
*/

#ifndef LVL_H
#define LVL_H

#include "struct.h"

void end_back(game_s *game);
void end_main_menu(game_s *game);

void actualize_txt(game_s *game);

void events_lvl(game_s *game, sfEvent event);
void draw_lvl_ext(game_s *game);

void pause_managing(game_s *game, sfEvent event);

#endif
