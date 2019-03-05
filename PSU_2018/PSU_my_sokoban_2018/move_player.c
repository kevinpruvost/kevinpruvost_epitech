/*
** EPITECH PROJECT, 2018
** move_player.c
** File description:
** functions to move P
*/

#include "include/my.h"
#include <curses.h>

char **rewrite_player(char **array, position *pl_b, position *pl, int i)
{
    array[pl_b->x][pl_b->y] = ' ';
    array[pl->x][pl->y] = 'P';
    return (array);
}

int check_collision(position *pl, char **array, int sens, int axe)
{
    int collision = 1;

    if (array[pl->x][pl->y] == 'O' || array[pl->x][pl->y] == ' ')
        collision = 0;
    if (axe == 1)
        if (array[pl->x][pl->y] == 'X' && \
        array[pl->x+sens][pl->y] != '#' && \
        array[pl->x+sens][pl->y] != 'X' && array[pl->x+sens][pl->y] >= 32) {
            collision = 0;
            array[pl->x + sens][pl->y] = 'X';
        }
    if (axe == 0)
        if (array[pl->x][pl->y] == 'X' && \
        array[pl->x][pl->y + sens] != '#' && \
        array[pl->x][pl->y + sens] != 'X' && array[pl->x][pl->y + sens] >= 32) {
            collision = 0;
            array[pl->x][pl->y + sens] = 'X';
        }
    return (collision);
}

void move_player2(char **array, position *player, int i)
{
    if (i == KEY_LEFT) {
        player->y = player->y - 1;
        if (check_collision(player, array, -1, 0) == 1)
            player->y = player->y + 1;
    }
    if (i == KEY_RIGHT) {
        player->y = player->y + 1;
        if (check_collision(player, array, 1, 0) == 1)
            player->y = player->y - 1;
    }
}

char **move_player(char **array, position *player, int i)
{
    position *player_before = malloc(sizeof(player_before));

    player_before->x = player->x;
    player_before->y = player->y;
    if (i == KEY_UP) {
        player->x = player->x - 1;
        if (check_collision(player, array, -1, 1) == 1)
            player->x = player->x + 1;
    }
    if (i == KEY_DOWN) {
        player->x = player->x + 1;
        if (check_collision(player, array, 1, 1) == 1)
            player->x = player->x - 1;
    }
    move_player2(array, player, i);
    array = rewrite_player(array, player_before, player, i);
    return (array);
}

position *find_player(char **array, position *player)
{
    for (int i = 0, j = 0; array[i] != 0; j++) {
        if (array[i][j] == 0 && array[i+1] != 0) {
            j = 0;
            i++;
        }
        if (array[i][j] == 0 && array[i+1] == 0)
            return (player);
        if (array[i][j] == 'P') {
            player->x = i;
            player->y = j;
            return (player);
        }
    }
    return (player);
}
