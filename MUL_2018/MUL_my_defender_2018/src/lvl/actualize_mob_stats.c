/*
** EPITECH PROJECT, 2019
** actualize_mob_stats.c
** File description:
** actualize mob stats
*/

#include "my.h"

void actualize_mob_stats(mob_t *mob, int lvl)
{
    mob->lvl = lvl;
    mob->hp += (mob->hp * lvl * 0.4);
    mob->speed += (mob->speed * lvl * 0.1);
}
