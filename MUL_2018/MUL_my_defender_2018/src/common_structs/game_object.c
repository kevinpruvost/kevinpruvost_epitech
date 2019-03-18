/*
** EPITECH PROJECT, 2018
** game_obj.c
** File description:
** game_obj functions
*/

#include "my.h"

void create_game_obj2(game_obj *go_created, sfClock *c)
{
    go_created->time_anim = create_time_obj(c);
    go_created->time_move = create_time_obj(c);
    go_created->origin.x = 0;
    go_created->origin.y = 0;
}

game_obj *create_game_obj(char *f, sfIntRect r, sfVector2f posi, sfClock *c)
{
    game_obj *go_created = malloc(sizeof(game_obj));
    sfVector2f s = {1, 1};

    go_created->color.r = 255;
    go_created->color.g = 255;
    go_created->color.b = 255;
    go_created->color.a = 255;
    go_created->sprite = sfSprite_create();
    go_created->texture = sfTexture_createFromFile(f, NULL);
    sfSprite_setTexture(go_created->sprite, go_created->texture, sfFalse);
    go_created->pos = posi;
    sfSprite_setPosition(go_created->sprite, go_created->pos);
    go_created->rect = r;
    sfSprite_setTextureRect(go_created->sprite, go_created->rect);
    go_created->scale = s;
    sfSprite_setScale(go_created->sprite, s);
    create_game_obj2(go_created, c);
    return (go_created);
}

void destroy_game_obj(game_obj *go_todestroy)
{
    sfSprite_destroy(go_todestroy->sprite);
    if (go_todestroy->texture != NULL)
        sfTexture_destroy(go_todestroy->texture);
    destroy_time_obj(go_todestroy->time_anim);
    destroy_time_obj(go_todestroy->time_move);
    free(go_todestroy);
}
