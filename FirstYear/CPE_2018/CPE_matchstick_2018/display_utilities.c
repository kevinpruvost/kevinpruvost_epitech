/*
** EPITECH PROJECT, 2019
** display_utilities.c
** File description:
** display
*/

#include "my.h"

void display_turn_player(int matches_ask, int line_ask)
{
    my_putstr("Player removed ");
    my_put_nbr(matches_ask);
    my_putstr(" match(es) from line ");
    my_put_nbr(line_ask);
    my_putchar('\n');
}

void error_display_matches(int max_remove)
{
    my_putstr("Error: you cannot remove more than ");
    my_put_nbr(max_remove);
    my_putstr(" matches per turn\n");
}
