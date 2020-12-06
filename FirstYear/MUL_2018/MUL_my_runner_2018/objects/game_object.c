/*
** EPITECH PROJECT, 2018
** game_obj.c
** File description:
** game_obj functions
*/

#include "my.h"

game_obj *create_game_obj(char *f, sfIntRect r, sfVector2f posi, sfVector2f s)
{
    game_obj *go_created = malloc(sizeof(game_obj));

    go_created->sprite = sfSprite_create();
    go_created->texture = sfTexture_createFromFile(f, NULL);
    sfSprite_setTexture(go_created->sprite, go_created->texture, sfFalse);
    go_created->pos = posi;
    sfSprite_setPosition(go_created->sprite, go_created->pos);
    go_created->rect = r;
    sfSprite_setTextureRect(go_created->sprite, go_created->rect);
    go_created->clock = sfClock_create();
    go_created->scale = s;
    sfSprite_setScale(go_created->sprite, s);
    return (go_created);
}

void destroy_game_obj(game_obj *go_todestroy)
{
    sfSprite_destroy(go_todestroy->sprite);
    sfTexture_destroy(go_todestroy->texture);
    sfClock_destroy(go_todestroy->clock);
    free(go_todestroy);
}
