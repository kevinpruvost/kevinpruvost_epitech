/*
** EPITECH PROJECT, 2018
** player_obj.c
** File description:
** player struct
*/

#include "my.h"

player_obj *player_rect_pos(player_obj *player, sfVector2f pos)
{
    player->rect.top = 0;
    player->rect.left = 0;
    player->rect.width = 43;
    player->rect.height = 52;
    player->pos.x = pos.x;
    player->pos.y = pos.y;
    return (player);
}

player_obj *create_player_obj(sfVector2f pos, sfVector2f scale)
{
    player_obj *player = malloc(sizeof(player_obj));

    player->scale.y = scale.y;
    player->scale.x = scale.x;
    player->anim_stade = 0;
    player->sprite = sfSprite_create();
    player->texture = sfTexture_createFromFile("sprites/shrek.png", NULL);
    sfSprite_setTexture(player->sprite, player->texture, sfFalse);
    player = player_rect_pos(player, pos);
    sfSprite_setPosition(player->sprite, player->pos);
    sfSprite_setTextureRect(player->sprite, player->rect);
    player->clock_anim = sfClock_create();
    player->clock_jump = sfClock_create();
    player->jump_mode = 0;
    sfSprite_setScale(player->sprite, scale);
    player->y_sol = 80 * 9;
    player->death_sound = create_sound_obj("sounds/pain.ogg");
    return (player);
}

void destroy_player_obj(player_obj *player)
{
    sfSprite_destroy(player->sprite);
    sfTexture_destroy(player->texture);
    sfClock_destroy(player->clock_anim);
    sfClock_destroy(player->clock_jump);
    destroy_sound_obj(player->death_sound);
    free(player);
}
