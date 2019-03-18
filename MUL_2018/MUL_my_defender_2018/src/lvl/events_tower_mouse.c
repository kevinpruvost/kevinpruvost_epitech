/*
** EPITECH PROJECT, 2019
** events_tower_mouse.c
** File description:
** events tower mouse
*/

#include "my.h"

void upgrade_sell_options2(game_s *game, sfEvent event, tower_t *tower)
{
    if (is_left_click(event, game->lvl_vars->cursor,
        game->lvl_vars->player->upgrade_button) == 1)
        upgrade_tower(game, tower);
    if (is_left_click(event, game->lvl_vars->cursor,
        game->lvl_vars->player->sell_button) == 1)
        sell_tower(game, tower);
}

void upgrade_sell_options(game_s *game, sfEvent event, tower_t *tower)
{
    mod_scale(game->lvl_vars->player->upgrade_button->sprite, 0.75);
    if (collision_cursor(game->lvl_vars->cursor,
        game->lvl_vars->player->upgrade_button) == 1)
        mod_scale(game->lvl_vars->player->upgrade_button->sprite, 1);
    mod_scale(game->lvl_vars->player->sell_button->sprite, 0.75);
    if (collision_cursor(game->lvl_vars->cursor,
        game->lvl_vars->player->sell_button) == 1)
        mod_scale(game->lvl_vars->player->sell_button->sprite, 1);
    upgrade_sell_options2(game, event, tower);
}

void events_tower_mouse2(game_s *game, sfEvent event, tower_t *towers_b)
{
    mod_scale(towers_b->props->sprite, 1);
    if (collision_cursor(game->lvl_vars->cursor,
        towers_b->props) == 1)
        mod_scale(towers_b->props->sprite, 1.25);
    if (is_left_click(event, game->lvl_vars->cursor,
        towers_b->props) == 1)
        game->lvl_vars->adress = &towers_b->props;
    mod_color(towers_b->props->sprite, 255, 255, 255);
    if (game->lvl_vars->adress == &towers_b->props) {
        mod_color(towers_b->props->sprite, 100, 255, 100);
        upgrade_sell_options(game, event, towers_b);
    }
}

void events_tower_mouse(game_s *game, sfEvent event)
{
    tower_t *towers = game->lvl_vars->towers;

    for (tower_t *towers_b = towers; towers_b != NULL; towers_b = towers) {
        (towers != NULL) ? (towers = towers->next) : (0);
        events_tower_mouse2(game, event, towers_b);
    }
}
