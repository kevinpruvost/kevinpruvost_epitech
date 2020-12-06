/*
** EPITECH PROJECT, 2019
** proj.c
** File description:
** proj struct
*/

#include "my.h"

proj_t *create_proj(proj_t *projs, tower_t *tow, lib_types_t *lib, game_s *game)
{
    projs->props = malloc(sizeof(game_obj));
    projs->props->texture = NULL;
    projs->props->pos.x = tow->props->pos.x - tow->props->origin.x;
    projs->props->pos.y = tow->props->pos.y - tow->props->origin.y;
    projs->props->sprite = sfSprite_create();
    sfSprite_setTexture(projs->props->sprite,
                        lib->texture_proj[tow->type], sfTrue);
    sfSprite_setPosition(projs->props->sprite, projs->props->pos);
    projs->props->time_anim = create_time_obj(game->clock);
    projs->props->time_move = create_time_obj(game->clock);
    projs->type = tow->type;
    projs->speed = 5;
    projs->damage = tow->damage;
    projs->next = NULL;
    projs->target = NULL;
    center_mob(projs->props);
    projs->props->origin.x -= projs->props->rect.width;
    projs->props->origin.y -= projs->props->rect.height;
    projs->arrived = 0;
    return (projs);
}

void add_new_proj(game_s *game, tower_t *tow, mob_t *mob)
{
    proj_t *projs = game->lvl_vars->projs;
    lib_types_t *lib = game->lvl_vars->lib_types;

    if (projs == NULL) {
        projs = malloc(sizeof(proj_t));
        projs = create_proj(projs, tow, lib, game);
        projs->target = &mob->props;
        sfSprite_setOrigin(projs->props->sprite, projs->props->origin);
        game->lvl_vars->projs = projs;
    } else {
        for (; projs->next != NULL; projs = projs->next);
        projs->next = malloc(sizeof(proj_t));
        projs->next = create_proj(projs->next, tow, lib, game);
        projs->next->target = &mob->props;
        sfSprite_setOrigin(projs->next->props->sprite,
        projs->next->props->origin);
    }
}

void destroy_proj(proj_t *projs, proj_t *proj_to_kill)
{
    if (projs == proj_to_kill) {
        if (projs->next != NULL)
            projs = projs->next;
        else
            projs = NULL;
    } else {
        while (projs->next != proj_to_kill)
            projs = projs->next;
        projs->next = projs->next->next;
    }
    destroy_game_obj(proj_to_kill->props);
    free(proj_to_kill);
}

proj_t *create_projs(void)
{
    return (NULL);
}

void destroy_projs(proj_t *projs)
{
    proj_t *proj1;

    if (projs != NULL) {
        while (projs->next != NULL) {
            proj1 = projs;
            projs = projs->next;
            destroy_game_obj(proj1->props);
            free(proj1);
        }
        destroy_game_obj(projs->props);
        free(projs);
    }
}
