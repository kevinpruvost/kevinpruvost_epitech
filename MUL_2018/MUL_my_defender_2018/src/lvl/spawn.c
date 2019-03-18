/*
** EPITECH PROJECT, 2019
** spawn.c
** File description:
** spawn mobs
*/

#include "my.h"

float create_spawn_time(game_s *game)
{
    float time = 1.5;

    time -= game->lvl_vars->player->wave * 0.05;
    if (time < 0.35)
        time = 0.5;
    return (time);
}

void spawn_mobs2(player_t *player, float seconds_wave, game_s *game)
{
    if (seconds_wave > 10) {
        player->wave += 1;
        sfMusic_play(game->sound_fx[NWAVE]);
        game->lvl_vars->next_waving = 1;
        reset_time(game->lvl_vars->next_wave->time_anim, game->clock);
        player->nb_mobs_to_spawn = 5 +
            player->wave * 3;
    }
}

void spawn_mobs(game_s *game)
{
    player_t *player = game->lvl_vars->player;
    float seconds_wave = get_time(player->time_wave, game->clock);
    float seconds_spawn = get_time(player->time_spawn, game->clock);
    float spawn_time = create_spawn_time(game);

    if (player->nb_mobs_to_spawn > 0 && game->start == 1) {
        if (seconds_spawn > spawn_time) {
            reset_time(player->time_spawn, game->clock);
            add_new_mob(game, rand() % 4, player->wave);
            player->nb_mobs_to_spawn -= 1;
            (player->nb_mobs_to_spawn == 0) ?
            (reset_time(player->time_wave, game->clock)) : (0);
        }
    } else if (game->start == 1)
        spawn_mobs2(player, seconds_wave, game);
}
