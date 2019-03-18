/*
** EPITECH PROJECT, 2019
** mob.c
** File description:
** mob struct
*/

#include "my.h"

void create_mob2(mob_t *mobs, int id, lib_types_t *lib, sfClock *c)
{
    sfIntRect r = {0, 0, 100, 5};
    sfVector2f pos = {0, 0};

    mobs->type = id;
    mobs->lvl = 1;
    mobs->speed = lib->speed_mob[id];
    mobs->hp = lib->hp_mob[id];
    mobs->next = NULL;
    mobs->path_pos = 0;
    mobs->health_bar = create_game_obj
    ("assets/sprites/health_bar.png", r, pos, c);
    center_hp(mobs->health_bar, mobs->props);
    mobs->slow = 0;
    mobs->dot = 0;
    mobs->time_dot = create_time_obj(c);
    mobs->time_slow = create_time_obj(c);
    mobs->props->origin.x = 0;
    mobs->props->origin.y = 0;
    mobs->props->rect.top = 0;
    mobs->props->rect.left = 0;
}

mob_t *create_mob(mob_t *mobs, int id, lib_types_t *lib, game_s *game)
{
    mobs->props = malloc(sizeof(game_obj));
    mobs->props->texture = NULL;
    mobs->props->pos.x = game->map->orders[1]->x * 100;
    mobs->props->pos.y = game->map->orders[1]->y * 100 - 100;
    mobs->props->sprite = sfSprite_create();
    sfSprite_setTexture(mobs->props->sprite,
    lib->texture_mob[id], sfTrue);
    mobs->props->rect = sfSprite_getTextureRect(mobs->props->sprite);
    mobs->props->rect.width = mobs->props->rect.width / 3;
    mobs->props->rect.height = mobs->props->rect.height / 2;
    sfSprite_setTextureRect(mobs->props->sprite, mobs->props->rect);
    sfSprite_setPosition(mobs->props->sprite, mobs->props->pos);
    mobs->props->time_anim = create_time_obj(game->clock);
    mobs->props->time_move = create_time_obj(game->clock);
    create_mob2(mobs, id, lib, game->clock);
    return (mobs);
}

void add_new_mob(game_s *game, int id, int wave)
{
    mob_t *mobs = game->lvl_vars->mobs;
    lib_types_t *lib = game->lvl_vars->lib_types;

    if (mobs == NULL) {
        mobs = malloc(sizeof(mob_t));
        mobs = create_mob(mobs, id, lib, game);
        mobs->arrived = 0;
        center_mob(mobs->props);
        game->lvl_vars->mobs = mobs;
        actualize_mob_stats(mobs, (int)((wave / 4) + 1));
    } else {
        for (; mobs->next != NULL; mobs = mobs->next);
        mobs->next = malloc(sizeof(mob_t));
        mobs->next = create_mob(mobs->next, id, lib, game);
        center_mob(mobs->next->props);
        mobs->next->arrived = 0;
        actualize_mob_stats(mobs->next, (int)((wave / 4) + 1));
    }
}

void kill_mob(mob_t *mobs, mob_t *mob_to_kill)
{
    if (mobs == mob_to_kill) {
        if (mobs->next != NULL) {
            mobs = mobs->next;
        } else
            mobs = NULL;
    } else {
        while (mobs->next != mob_to_kill)
            mobs = mobs->next;
        mobs->next = mobs->next->next;
    }
    destroy_game_obj(mob_to_kill->props);
    destroy_game_obj(mob_to_kill->health_bar);
    destroy_time_obj(mob_to_kill->time_dot);
    destroy_time_obj(mob_to_kill->time_slow);
    free(mob_to_kill);
}

void destroy_mobs(mob_t *mobs)
{
    mob_t *mob1;

    if (mobs != NULL) {
        while (mobs->next != NULL) {
            mob1 = mobs;
            mobs = mobs->next;
            destroy_game_obj(mob1->props);
            destroy_game_obj(mob1->health_bar);
            destroy_time_obj(mob1->time_dot);
            destroy_time_obj(mob1->time_slow);
            free(mob1);
        }
        destroy_game_obj(mobs->props);
        destroy_game_obj(mobs->health_bar);
        destroy_time_obj(mobs->time_dot);
        destroy_time_obj(mobs->time_slow);
        free(mobs);
    }
}
