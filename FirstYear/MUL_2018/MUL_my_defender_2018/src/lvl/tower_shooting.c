/*
** EPITECH PROJECT, 2019
** tower_shooting.c
** File description:
** tower shooting funcs
*/

#include "my.h"

mob_t *identify_mob(game_s *game, void *adress)
{
    mob_t *mobs = game->lvl_vars->mobs;

    for (; mobs != NULL; mobs = mobs->next) {
        if (&mobs->props == adress)
            return (mobs);
    }
    return (NULL);
}

void follow_proj(game_s *game)
{
    proj_t *projs = game->lvl_vars->projs;
    mob_t *mobs;

    for (; projs != NULL; projs = projs->next, mobs = NULL) {
        mobs = identify_mob(game, projs->target);
        if (mobs != NULL) {
            move_proj_to_mob(projs, mobs, game->clock);
        }
    }
}

int verif_slow(tower_t *tow, mob_t *mob)
{
    if (tow->type != SLOW)
        return (1);
    if (tow->type == SLOW && mob->slow == 1)
        return (0);
    if (tow->type == SLOW && mob->slow == 0)
        return (1);
    return (1);
}

int tower_shooting_verify(game_s *game, float spd, tower_t *tow, mob_t *mobs)
{
    int sound_id = SFD;

    if (is_in_radius(tow->props, mobs->props, tow->range) == 1
        && spd >= tow->atk_speed / 3 && verif_slow(tow, mobs) == 1) {
        tow->firing = 1;
        add_new_proj(game, tow, mobs);
        tow->props->rect.top = 0;
        if (tow->props->pos.x > mobs->props->pos.x)
            tow->props->rect.top = tow->props->rect.height;
        if (tow->type == HEAVY)
            sound_id = DRAGON;
        sfMusic_play(game->sound_fx[sound_id]);
        sfSprite_setTextureRect(tow->props->sprite, tow->props->rect);
        reset_time(tow->atk_speed_time, game->clock);
        return (1);
    }
    return (0);
}

void tower_shooting(game_s *game)
{
    tower_t *towers = game->lvl_vars->towers;
    mob_t *mobs = game->lvl_vars->mobs;

    follow_proj(game);
    proj_damage(game);
    for (float atk_spd = 0; towers != NULL; towers = towers->next) {
        atk_spd = get_time(towers->atk_speed_time, game->clock);
        for (mobs = game->lvl_vars->mobs; mobs != NULL; mobs = mobs->next) {
            (tower_shooting_verify(game, atk_spd, towers, mobs) == 1)
            ? (atk_spd = 0) : (0);
        }
    }
}
