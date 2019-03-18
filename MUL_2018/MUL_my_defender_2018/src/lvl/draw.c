/*
** EPITECH PROJECT, 2019
** draw.c
** File description:
** draw functions
*/

#include "my.h"

void draw_mobs(game_s *game)
{
    mob_t *mobs = game->lvl_vars->mobs;
    sfIntRect rect = {0, 0, 0, 5};

    for (; mobs != NULL; mobs = mobs->next) {
        rect.width = mobs->hp / 6 + 1;
        mobs->health_bar->rect = rect;
        sfSprite_setTextureRect(mobs->health_bar->sprite,
        mobs->health_bar->rect);
        mobs->health_bar->pos = mobs->props->pos;
        mobs->health_bar->pos.y += mobs->props->rect.height;
        sfSprite_setPosition(mobs->health_bar->sprite, mobs->health_bar->pos);
        sfRenderWindow_drawSprite(game->win, mobs->props->sprite, NULL);
        sfRenderWindow_drawSprite(game->win, mobs->health_bar->sprite, NULL);
    }
}

void draw_towers(game_s *game)
{
    tower_t *towers = game->lvl_vars->towers;

    for (; towers != NULL; towers = towers->next) {
        sfRenderWindow_drawSprite(game->win, towers->props->sprite, NULL);
    }
}

void draw_projs(game_s *game)
{
    proj_t *projs = game->lvl_vars->projs;

    for (; projs != NULL; projs = projs->next) {
        sfRenderWindow_drawSprite(game->win, projs->props->sprite, NULL);
    }
}

void draw_start_button(game_s *game)
{
    if (game->start == 0)
        sfRenderWindow_drawSprite
        (game->win, game->start_button->sprite, NULL);
}

void draw_lvl_ext(game_s *game)
{
    sfRenderWindow_clear(game->win, sfTransparent);
    sfRenderWindow_drawSprite(game->win,
    game->lvl_vars->background->sprite, NULL);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 6; j++)
            sfRenderWindow_drawSprite
                (game->win, game->map->map_case[i][j]->sprite, NULL);
    draw_mobs(game);
    draw_towers(game);
    draw_projs(game);
    draw_lvl_ext2(game);
    for (int i = 0; i < 4; i++) {
        sfRenderWindow_drawSprite
            (game->win, game->lvl_vars->player->tower_buttons[i]->sprite, NULL);
        sfRenderWindow_drawSprite
            (game->win, game->lvl_vars->player->tower_descs[i]->sprite, NULL);
    }
    draw_start_button(game);
    display_tower_info(game);
}
