/*
** EPITECH PROJECT, 2019
** pause.c
** File description:
** pause functions
*/

#include "my.h"

void pause_end(game_s *game)
{
    game->lvl_vars->pause *= -1;
    destroy_lvl_s(game->lvl_vars);
    game->lvl_vars = create_lvl_s(game->clock);
    game->start = 0;
    change_page(game, MAINMENU);
}

void pause_buttons2(game_s *game, sfEvent event)
{
    if (is_left_click(event, game->lvl_vars->cursor,
        game->lvl_vars->pause_objs[1]) == 1) {
        pause_resume(game);
        sfMusic_play(game->beep);
        game->lvl_vars->pause *= -1;
    }
    if (is_left_click(event, game->lvl_vars->cursor,
        game->lvl_vars->pause_objs[2]) == 1) {
        pause_end(game);
        sfMusic_play(game->beep);
    }
    if (event.type == sfEvtKeyPressed
        && event.key.code == sfKeyH && game->lvl_vars->pause == 1)
        change_page(game, HTP);
}

void pause_buttons(game_s *game, sfEvent event)
{
    for (int i = 1; i < 3; i++) {
        mod_scale(game->lvl_vars->pause_objs[i]->sprite, 1);
        if (collision_cursor(game->lvl_vars->cursor,
            game->lvl_vars->pause_objs[i]) == 1)
            mod_scale(game->lvl_vars->pause_objs[i]->sprite, 1.25);
    }
    pause_buttons2(game, event);
}

void pause_managing(game_s *game, sfEvent event)
{
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyEscape) {
        if (game->lvl_vars->pause == 1)
            pause_resume(game);
        game->lvl_vars->pause *= -1;
        game->lvl_vars->adress = NULL;
    }
    if (game->lvl_vars->pause == 1) {
        pause_buttons(game, event);
    }
}
