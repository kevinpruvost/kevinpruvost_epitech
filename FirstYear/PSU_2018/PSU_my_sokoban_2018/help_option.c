/*
** EPITECH PROJECT, 2018
** help_option.c
** File description:
** -h addition
*/

#include "include/my.h"
#include <curses.h>

void help_option(void)
{
    char *message = "USAGE\n"
    "     ./my_sokoban map\n"
    "DESCRIPTION\n"
    "     map  file representing the warehouse map, containing"
    "'#' for walls,\n"
    "          'P' for the player, 'X' for the boxes and 'O' "
    "for storage locations.\n";

    my_putstr(message);
}
