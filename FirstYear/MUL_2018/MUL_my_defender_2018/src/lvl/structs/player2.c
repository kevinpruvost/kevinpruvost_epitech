/*
** EPITECH PROJECT, 2019
** player2.c
** File description:
** player2
*/

#include "my.h"

game_obj *create_upgrade_button(sfClock *clock)
{
    sfIntRect rect = {0, 0, 100, 50};
    sfVector2f pos = {85, 755};
    game_obj *obj = create_game_obj("assets/sprites/upgrade_button.png",
    rect, pos, clock);

    center_game_object(obj);
    return (obj);
}

game_obj *create_sell_button(sfClock *clock)
{
    sfIntRect rect = {0, 0, 100, 50};
    sfVector2f pos = {205, 755};
    game_obj *obj = create_game_obj("assets/sprites/sell_button.png",
    rect, pos, clock);

    center_game_object(obj);
    return (obj);
}

void create_spectres_player2(player_t *player, sfVector2f origin)
{
    sfIntRect rect = sfSprite_getTextureRect
    (player->tower_spectres[HEAVY]->sprite);

    sfSprite_setOrigin(player->tower_spectres[DMG]->sprite, origin);
    sfSprite_setOrigin(player->tower_spectres[DOT]->sprite, origin);
    sfSprite_setOrigin(player->tower_spectres[SLOW]->sprite, origin);
    player->tower_spectres[DMG]->origin = origin;
    player->tower_spectres[DOT]->origin = origin;
    player->tower_spectres[SLOW]->origin = origin;
    origin.x = rect.width / 2;
    origin.y = rect.height / 2;
    sfSprite_setOrigin(player->tower_spectres[HEAVY]->sprite, origin);
    player->tower_spectres[HEAVY]->origin = origin;
}

void create_spectres_player(player_t *player, sfClock *clock)
{
    sfVector2f pos = {0, 0};
    sfIntRect rect = {0, 0, 50, 50};
    sfColor color = {255, 255, 255, 125};
    sfVector2f origin = {rect.width / 2, rect.height / 2};

    player->tower_spectres[DMG] = create_game_obj
        ("assets/sprites/fiona_sprite.png", rect, pos, clock);
    player->tower_spectres[DOT] = create_game_obj
        ("assets/sprites/shrek_sprite.png", rect, pos, clock);
    player->tower_spectres[SLOW] = create_game_obj
        ("assets/sprites/donkey_sprite.png", rect, pos, clock);
    rect.width = 90;
    rect.height = 90;
    player->tower_spectres[HEAVY] = create_game_obj
        ("assets/sprites/dragon_sprite.png", rect, pos, clock);
    sfSprite_setColor(player->tower_spectres[DMG]->sprite, color);
    sfSprite_setColor(player->tower_spectres[DOT]->sprite, color);
    sfSprite_setColor(player->tower_spectres[SLOW]->sprite, color);
    sfSprite_setColor(player->tower_spectres[HEAVY]->sprite, color);
    create_spectres_player2(player, origin);
}
