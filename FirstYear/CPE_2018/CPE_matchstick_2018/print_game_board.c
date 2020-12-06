/*
** EPITECH PROJECT, 2019
** print_game_board.c
** File description:
** print game board
*/

#include <unistd.h>
#include "my.h"

void print_game_board(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        my_putstr(arr[i]);
        my_putchar('\n');
    }
}
