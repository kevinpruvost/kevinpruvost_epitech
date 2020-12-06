/*
** EPITECH PROJECT, 2019
** draw.c
** File description:
** draw funcs for map editor
*/

#include "my.h"

void draw_map_editor2(game_s *game)
{
    sfRenderWindow *win = game->win;
    map_editor_s *maped_vars = game->maped_vars;

    sfRenderWindow_drawSprite(win, maped_vars->grid->sprite, NULL);
    sfRenderWindow_drawSprite(win, maped_vars->return_button->sprite, NULL);
    sfRenderWindow_drawSprite(win, maped_vars->clear_button->sprite, NULL);
    sfRenderWindow_drawSprite(win, maped_vars->clear_desc->sprite, NULL);
    sfRenderWindow_drawSprite(win, maped_vars->remove_button->sprite, NULL);
    sfRenderWindow_drawSprite(win, maped_vars->remove_desc->sprite, NULL);
    sfRenderWindow_drawSprite(win, maped_vars->random_button->sprite, NULL);
    sfRenderWindow_drawSprite(win, maped_vars->random_desc->sprite, NULL);
    sfRenderWindow_drawSprite(win, maped_vars->not_valid->sprite, NULL);
    sfRenderWindow_drawSprite(win, maped_vars->return_desc->sprite, NULL);
    sfRenderWindow_drawSprite(win,
    maped_vars->cursor->sprite, NULL);
    sfRenderWindow_display(win);
}

void draw_map_editor1(game_s *game)
{
    sfRenderWindow_clear(game->win, sfTransparent);
    sfRenderWindow_drawSprite(game->win,
    game->maped_vars->background->sprite, NULL);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 6; j++) {
            sfRenderWindow_drawSprite
                (game->win, game->map->map_case[i][j]->sprite, NULL);
            sfRenderWindow_drawSprite
                (game->win, game->maped_vars->p_cases[i][j]->sprite, NULL);
        }
}

void draw_map_editor(game_s *game)
{
    draw_map_editor1(game);
    draw_map_editor2(game);
}
