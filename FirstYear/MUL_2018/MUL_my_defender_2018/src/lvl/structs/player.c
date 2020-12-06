/*
** EPITECH PROJECT, 2019
** player.c
** File description:
** player structs
*/

#include "my.h"

void create_desc_player(player_t *player, sfClock *clock)
{
    sfVector2f pos = {690, 490};
    sfIntRect rect = {0, 0, 300, 300};
    sfColor color = {255, 255, 255, 0};

    player->tower_descs[DMG] = create_game_obj
        ("assets/sprites/fiona_desc.png", rect, pos, clock);
    player->tower_descs[DOT] = create_game_obj
        ("assets/sprites/shrek_desc.png", rect, pos, clock);
    player->tower_descs[SLOW] = create_game_obj
        ("assets/sprites/donkey_desc.png", rect, pos, clock);
    player->tower_descs[HEAVY] = create_game_obj
        ("assets/sprites/dragon_desc.png", rect, pos, clock);
    sfSprite_setColor(player->tower_descs[DMG]->sprite, color);
    sfSprite_setColor(player->tower_descs[DOT]->sprite, color);
    sfSprite_setColor(player->tower_descs[SLOW]->sprite, color);
    sfSprite_setColor(player->tower_descs[HEAVY]->sprite, color);
}

void create_button_player(player_t *player, sfClock *clock)
{
    sfVector2f pos = {350, 890};
    sfIntRect rect = {0, 0, 100, 100};
    sfVector2f origin = {rect.width / 2, rect.height / 2};

    player->tower_buttons[DMG] = create_game_obj
        ("assets/sprites/fiona.png", rect, pos, clock);
    pos.x += 125;
    player->tower_buttons[DOT] = create_game_obj
        ("assets/sprites/shrek.png", rect, pos, clock);
    pos.x += 125;
    player->tower_buttons[SLOW] = create_game_obj
        ("assets/sprites/donkey.png", rect, pos, clock);
    pos.x += 125;
    player->tower_buttons[HEAVY] = create_game_obj
        ("assets/sprites/dragon.png", rect, pos, clock);
    for (int i = 0; i < 4; i++) {
        sfSprite_setOrigin(player->tower_buttons[i]->sprite, origin);
        player->tower_buttons[i]->origin = origin;
        mod_scale(player->tower_buttons[i]->sprite, 0.75);
    }
}

void create_txt_player(player_t *player)
{
    sfColor co = {100, 255, 50, 255};
    sfVector2f sc = {1, 1};
    sfVector2f pos = {810, 815};

    player->wave_txt = create_text_obj("Wave :  ", sc, pos, co);
    pos.y += 40;
    player->hp_txt = create_text_obj("HP :    ", sc, pos, co);
    pos.y += 40;
    player->money_txt = create_text_obj("Money : ", sc, pos, co);
}

player_t *create_player(sfClock *clock)
{
    player_t *player = malloc(sizeof(player_t));

    player->money = 500;
    player->hp = 100;
    player->wave = 1;
    player->nb_mobs_to_spawn = 5;
    create_txt_player(player);
    create_button_player(player, clock);
    create_desc_player(player, clock);
    create_spectres_player(player, clock);
    player->time_wave = create_time_obj(clock);
    player->time_played = create_time_obj(clock);
    player->time_spawn = create_time_obj(clock);
    player->upgrade_button = create_upgrade_button(clock);
    player->sell_button = create_sell_button(clock);
    return (player);
}

void destroy_player(player_t *player)
{
    destroy_time_obj(player->time_played);
    destroy_time_obj(player->time_wave);
    destroy_time_obj(player->time_spawn);
    destroy_text_obj(player->money_txt);
    destroy_text_obj(player->hp_txt);
    destroy_text_obj(player->wave_txt);
    for (int i = 0; i < 4; i++) {
        destroy_game_obj(player->tower_buttons[i]);
        destroy_game_obj(player->tower_descs[i]);
        destroy_game_obj(player->tower_spectres[i]);
    }
    free(player);
}
