/*
** EPITECH PROJECT, 2019
** create_loading_bars.c
** File description:
** loading bars
*/

#include "my.h"

game_obj **create_music_bar(sfClock *clock)
{
    game_obj **music_bar = malloc(sizeof(game_obj *) * 11);
    sfIntRect rect = {0, 0, 40, 100};
    sfVector2f pos = {300, 150};

    music_bar[10] = NULL;
    for (int i = 0; i < 10; i++) {
        music_bar[i] = create_game_obj("assets/sprites/loading_tile.png",
        rect, pos, clock);
        pos.x += 50;
    }
    return (music_bar);
}

game_obj **create_sound_bar(sfClock *clock)
{
    game_obj **sound_bar = malloc(sizeof(game_obj *) * 11);
    sfIntRect rect = {0, 0, 40, 100};
    sfVector2f pos = {300, 300};

    sound_bar[10] = NULL;
    for (int i = 0; i < 10; i++) {
        sound_bar[i] = create_game_obj("assets/sprites/loading_tile.png",
        rect, pos, clock);
        pos.x += 50;
    }
    return (sound_bar);
}

void destroy_bars(game_obj **bar)
{
    int size = 0;

    for (; bar[size] != NULL; size++);
    size--;
    for (int i = size; i >= 0; i--) {
        destroy_game_obj(bar[i]);
    }
    free(bar);
}
