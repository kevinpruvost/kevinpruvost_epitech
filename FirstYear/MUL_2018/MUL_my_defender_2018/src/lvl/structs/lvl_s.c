/*
** EPITECH PROJECT, 2019
** lvl.s
** File description:
** lvl structs
*/

#include "my.h"

void create_pause_objs(sfClock *cl, game_obj *pause_objs[3])
{
    sfVector2f pos = {500, 400};
    sfIntRect rect = {0, 0, 300, 200};
    sfVector2f origin = {rect.width / 2, rect.height / 2};

    pause_objs[0] = create_game_obj("assets/sprites/pause.png", rect, pos, cl);
    sfSprite_setOrigin(pause_objs[0]->sprite, origin);
    pause_objs[0]->origin = origin;
    rect.width = 100;
    rect.height = 50;
    pos.x = 425;
    pos.y = 450;
    pause_objs[1] = create_game_obj("assets/sprites/resume.png", rect, pos, cl);
    origin.x = rect.width / 2;
    origin.y = rect.height / 2;
    sfSprite_setOrigin(pause_objs[1]->sprite, origin);
    pause_objs[1]->origin = origin;
    pos.x = 575;
    pause_objs[2] = create_game_obj("assets/sprites/quit.png", rect, pos, cl);
    sfSprite_setOrigin(pause_objs[2]->sprite, origin);
    pause_objs[2]->origin = origin;
}

void create_next_wave_obj(lvl_s *lvl_vars, sfClock *clock)
{
    sfIntRect rect = {0, 0, 400, 200};
    sfVector2f pos = {500, 500};
    sfVector2f origin = {rect.width / 2, rect.height / 2};

    lvl_vars->next_wave = create_game_obj
    ("assets/sprites/next_wave.png", rect, pos, clock);
    lvl_vars->next_wave->origin = origin;
    sfSprite_setOrigin(lvl_vars->next_wave->sprite, origin);
    lvl_vars->next_waving = 0;
}

lvl_s *create_lvl_s(sfClock *clock)
{
    lvl_s *lvl_vars = malloc(sizeof(lvl_s));
    sfIntRect bgd_rect = {0, 0, 1000, 1000};
    sfVector2f bgd_scale = {1, 1};

    lvl_vars->background = create_bgd_obj("assets/bgd/level_bgd.png",
    bgd_rect, bgd_scale);
    lvl_vars->grid = create_grid();
    lvl_vars->cursor = create_cursor(clock);
    lvl_vars->pause = -1;
    create_pause_objs(clock, lvl_vars->pause_objs);
    lvl_vars->player = create_player(clock);
    lvl_vars->towers = NULL;
    lvl_vars->projs = create_projs();
    lvl_vars->mobs = NULL;
    lvl_vars->lib_types = create_lib_types();
    lvl_vars->no_tower_info =
        create_tower_infos(lvl_vars->tower_infos, lvl_vars->no_tower_info);
    lvl_vars->adress = NULL;
    create_next_wave_obj(lvl_vars, clock);
    return (lvl_vars);
}

void destroy_lvl_s(lvl_s *lvl)
{
    destroy_bgd_obj(lvl->background);
    destroy_bgd_obj(lvl->grid);
    destroy_game_obj(lvl->cursor);
    destroy_towers(lvl->towers);
    destroy_projs(lvl->projs);
    destroy_player(lvl->player);
    destroy_mobs(lvl->mobs);
    destroy_lib_types(lvl->lib_types);
    for (int i = 0; i < 3; i++)
        destroy_game_obj(lvl->pause_objs[i]);
    for (int i = 0; i < 5; i++)
        destroy_text_obj(lvl->tower_infos[i]);
    destroy_text_obj(lvl->no_tower_info);
    destroy_game_obj(lvl->next_wave);
    free(lvl);
}
