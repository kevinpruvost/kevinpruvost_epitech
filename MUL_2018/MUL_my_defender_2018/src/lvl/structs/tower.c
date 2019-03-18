/*
** EPITECH PROJECT, 2019
** tower.c
** File description:
** tower struct
*/

#include "my.h"

void create_tower2(tower_t *towers, lib_types_t *lib, int id)
{
    towers->type = id;
    towers->lvl = 1;
    towers->atk_speed = lib->atk_speed_tower[id];
    towers->damage = lib->damage_tower[id];
    towers->range = lib->range_tower[id];
    towers->firing = 0;
    towers->props->origin.x = 0;
    towers->props->origin.y = 0;
    towers->props->rect.top = 0;
    towers->props->rect.left = 0;
}

tower_t *create_tower(tower_t *towers, int id, lib_types_t *lib, game_s *game)
{
    towers->props = malloc(sizeof(game_obj));
    towers->props->texture = NULL;
    towers->props->pos.x = game->map->orders[1]->x;
    towers->props->pos.y = game->map->orders[1]->y - 100;
    towers->props->sprite = sfSprite_create();
    sfSprite_setTexture(towers->props->sprite,
                        lib->texture_tower[id], sfTrue);
    towers->props->rect = sfSprite_getTextureRect(towers->props->sprite);
    towers->props->rect.width = towers->props->rect.width / 3;
    towers->props->rect.height = towers->props->rect.height / 2;
    sfSprite_setTextureRect(towers->props->sprite, towers->props->rect);
    sfSprite_setPosition(towers->props->sprite, towers->props->pos);
    towers->props->time_anim = create_time_obj(game->clock);
    towers->props->time_move = create_time_obj(game->clock);
    towers->atk_speed_time = create_time_obj(game->clock);
    create_tower2(towers, lib, id);
    return (towers);
}

void add_new_tower(game_s *game, int id, sfVector2f pos)
{
    tower_t *towers = game->lvl_vars->towers;
    lib_types_t *lib = game->lvl_vars->lib_types;

    if (towers == NULL) {
        towers = malloc(sizeof(tower_t));
        towers = create_tower(towers, id, lib, game);
        towers->next = NULL;
        sfSprite_setPosition(towers->props->sprite, pos);
        center_game_object(towers->props);
        towers->props->pos = pos;
        game->lvl_vars->towers = towers;
    } else {
        for (; towers->next != NULL; towers = towers->next);
        towers->next = malloc(sizeof(tower_t));
        towers->next = create_tower(towers->next, id, lib, game);
        towers->next->next = NULL;
        sfSprite_setPosition(towers->next->props->sprite, pos);
        towers->next->props->pos = pos;
        center_game_object(towers->next->props);
    }
}

void destroy_tower(tower_t *towers, tower_t *tower_to_kill)
{
    if (towers == tower_to_kill) {
        if (towers->next != NULL)
            towers = towers->next;
        else
            towers = NULL;
    } else {
        while (towers->next != tower_to_kill)
            towers = towers->next;
        towers->next = towers->next->next;
    }
    destroy_game_obj(tower_to_kill->props);
    destroy_time_obj(tower_to_kill->atk_speed_time);
    free(tower_to_kill);
}

void destroy_towers(tower_t *towers)
{
    tower_t *tower1;

    if (towers != NULL) {
        while (towers->next != NULL) {
            tower1 = towers;
            towers = towers->next;
            destroy_game_obj(tower1->props);
            destroy_time_obj(tower1->atk_speed_time);
            free(tower1);
        }
        destroy_game_obj(towers->props);
        destroy_time_obj(towers->atk_speed_time);
        free(towers);
    }
}
