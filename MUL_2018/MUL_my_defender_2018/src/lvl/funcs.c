/*
** EPITECH PROJECT, 2019
** funcs.c
** File description:
** main funcs of lvl
*/

#include "my.h"

void draw_lvl(game_s *game)
{
    draw_lvl_ext(game);
    sfRenderWindow_drawText
        (game->win, game->lvl_vars->player->money_txt->text, NULL);
    sfRenderWindow_drawText
        (game->win, game->lvl_vars->player->hp_txt->text, NULL);
    sfRenderWindow_drawText
        (game->win, game->lvl_vars->player->wave_txt->text, NULL);
    if (game->lvl_vars->pause == 1)
        for (int i = 0; i < 3; i++)
            sfRenderWindow_drawSprite
                (game->win, game->lvl_vars->pause_objs[i]->sprite, NULL);
    sfRenderWindow_drawSprite(game->win, game->lvl_vars->cursor->sprite, NULL);
    sfRenderWindow_display(game->win);
}

void event_lvl2(game_s *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->win, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(game->win);
        pause_managing(game, event);
        if (game->lvl_vars->pause != 1) {
            events_lvl(game, event);
        }
    }
}

void mouse_follow(game_s *game)
{
    sfVector2i local_pos = sfMouse_getPositionRenderWindow(game->win);

    game->lvl_vars->cursor->pos.x = local_pos.x;
    game->lvl_vars->cursor->pos.y = local_pos.y;
    sfSprite_setPosition(game->lvl_vars->cursor->sprite,
    game->lvl_vars->cursor->pos);
    for (int i = 0; i < 4; i++) {
        game->lvl_vars->player->tower_spectres[i]->pos.x = local_pos.x;
        game->lvl_vars->player->tower_spectres[i]->pos.y = local_pos.y;
        sfSprite_setPosition
        (game->lvl_vars->player->tower_spectres[i]->sprite,
        game->lvl_vars->player->tower_spectres[i]->pos);
        if (i < 2) {
            game->range[i]->pos.x = local_pos.x;
            game->range[i]->pos.y = local_pos.y;
            sfSprite_setPosition(game->range[i]->sprite, game->range[i]->pos);
        }
    }
}

void event_lvl(game_s *game)
{
    mouse_follow(game);
    event_lvl2(game);
    actualize_txt(game);
    if (game->lvl_vars->pause != 1) {
        spawn_mobs(game);
        mobs_move(game);
        mob_damage(game);
        end_game(game);
        mob_killed(game);
        tower_shooting(game);
        slow_behaviour(game);
        dot_behaviour(game);
        animation_mobs(game);
        animation_towers(game);
    }
}
