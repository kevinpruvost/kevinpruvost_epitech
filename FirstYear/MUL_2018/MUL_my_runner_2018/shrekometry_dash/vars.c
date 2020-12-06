/*
** EPITECH PROJECT, 2018
** vars.c
** File description:
** vars for the game
*/

#include "my.h"

game_obj *cursor_game_create(w_prop *win)
{
    game_obj *cursor;
    sfIntRect rect = {0, 0, 64, 64};
    sfVector2f scale = {win->scale.x / 2.0, win->scale.y / 2.0};
    sfVector2f pos = {0, 0};

    cursor = create_game_obj("sprites/cursor.png", rect, pos, scale);
    return (cursor);
}

game_obj *create_pause_txt(sfVector2f scale)
{
    game_obj *pause_txt;
    sfVector2f pos = {260 * scale.x, 350 * scale.y};
    sfIntRect rect = {0, 0, 320, 160};

    pause_txt = create_game_obj("sprites/pause_button.png", rect, pos, scale);
    return (pause_txt);
}

game_obj *create_block(int mode, sfVector2f scale, int i, int j)
{
    game_obj *block;
    sfIntRect rect = {0, 0, 81, 81};
    sfVector2f pos = {j * 80 * scale.y, i * 80 * scale.x};

    if (mode == 1)
        block = create_game_obj("sprites/floor_block.png", rect, pos, scale);
    if (mode == 2)
        block = create_game_obj("sprites/pikes.png", rect, pos, scale);
    if (mode == 3)
        block = create_game_obj("sprites/dirt_block.png", rect, pos, scale);
    if (mode == 4)
        block = create_game_obj("sprites/air.png", rect, pos, scale);
    return (block);
}

gm_vars *create_gm_vars2(gm_vars *gm)
{
    gm->stop = 0;
    gm->alive = 1;
    gm->pause = 0;
    gm->speed = 250;
    return (gm);
}

gm_vars *create_gm_vars(w_prop *win, char **map)
{
    gm_vars *gm = malloc(sizeof(gm_vars));
    sfIntRect rect = {0, 0, 800, 800};
    sfVector2f p_scale = {2 * win->scale.x, 2 * win->scale.y};
    sfVector2f p_pos = {52 * p_scale.x, (win->height - 264) * win->scale.y};
    sfVector2f b_pos = {0, 0};

    gm->map = map_vars_create(map, win->scale);
    gm = create_gm_vars2(gm);
    gm->gravity_clock = sfClock_create();
    gm->pause_txt = create_pause_txt(win->scale);
    gm->jump_sound = create_sound_obj("sounds/jump_sound.ogg");
    gm->back0 = create_bgd_obj("sprites/background.png", rect, win->scale);
    gm->back1 = create_bgd_obj("sprites/scene_back.png", rect, win->scale);
    gm->back2 = create_bgd_obj("sprites/scene.png", rect, win->scale);
    sfSprite_setPosition(gm->back1->sprite, b_pos);
    sfSprite_setPosition(gm->back2->sprite, b_pos);
    gm->player = create_player_obj(p_pos, p_scale);
    gm->cursor = cursor_game_create(win);
    gm->death_clock = sfClock_create();
    return (gm);
}
