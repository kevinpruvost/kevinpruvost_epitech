/*
** EPITECH PROJECT, 2018
** free.c
** File description:
** to destroy and free everything
*/

#include "my.h"

void destroy_game(gm_vars *gm)
{
    sfClock_destroy(gm->gravity_clock);
    destroy_game_obj(gm->pause_txt);
    destroy_bgd_obj(gm->back0);
    destroy_bgd_obj(gm->back1);
    destroy_bgd_obj(gm->back2);
    destroy_player_obj(gm->player);
    destroy_game_obj(gm->cursor);
    destroy_sound_obj(gm->jump_sound);
    free(gm);
}
