/*
** EPITECH PROJECT, 2019
** pause_resume.c
** File description:
** pause resume functions
*/

#include "my.h"

void pause_resume_mob(lvl_s *lvl_vars, sfClock *clock)
{
    mob_t *mobs = lvl_vars->mobs;

    if (mobs != NULL)
        for (; mobs != NULL; mobs = mobs->next) {
            end_pause_time(mobs->props->time_anim, clock);
            end_pause_time(mobs->props->time_move, clock);
        }
}

void pause_resume_proj(lvl_s *lvl_vars, sfClock *clock)
{
    proj_t *projs = lvl_vars->projs;

    if (projs != NULL)
        for (; projs != NULL; projs = projs->next) {
            end_pause_time(projs->props->time_anim, clock);
            end_pause_time(projs->props->time_move, clock);
        }
}

void pause_resume_tow_mob_proj(lvl_s *lvl_vars, sfClock *clock)
{
    tower_t *towers = lvl_vars->towers;

    if (towers != NULL)
        for (; towers != NULL; towers = towers->next) {
            end_pause_time(towers->atk_speed_time, clock);
            end_pause_time(towers->props->time_anim, clock);
            end_pause_time(towers->props->time_move, clock);
        }
    pause_resume_proj(lvl_vars, clock);
    pause_resume_mob(lvl_vars, clock);
}

void pause_resume(game_s *game)
{
    sfClock *clock = game->clock;
    player_t *player = game->lvl_vars->player;

    end_pause_time(player->time_spawn, clock);
    end_pause_time(player->time_wave, clock);
    end_pause_time(player->time_played, clock);
    pause_resume_tow_mob_proj(game->lvl_vars, clock);
}
