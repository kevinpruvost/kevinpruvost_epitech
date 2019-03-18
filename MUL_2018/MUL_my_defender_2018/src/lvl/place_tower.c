/*
** EPITECH PROJECT, 2019
** place_tower.c
** File description:
** place tower
*/

#include "my.h"

collision_t *create_coll_place_tower(game_obj *tower)
{
    collision_t *coll = malloc(sizeof(collision_t));

    coll->x01 = tower->pos.x - tower->origin.x;
    coll->x02 = tower->pos.x - tower->origin.x + tower->rect.width;
    coll->x11 = 0;
    coll->x12 = 1000;
    coll->y01 = tower->pos.y - tower->origin.y;
    coll->y02 = tower->pos.y - tower->origin.y + tower->rect.height;
    coll->y11 = 670;
    coll->y12 = 1000;
    return (coll);
}

int not_in_ui(game_obj *tower)
{
    collision_t *coll = create_coll_place_tower(tower);
    int collision_x = 0;
    int collision_y = 0;

    if ((coll->x01 >= coll->x11 && coll->x01 <= coll->x12) ||
        (coll->x02 >= coll->x11 && coll->x02 <= coll->x12))
        collision_x = 1;
    if ((coll->y01 >= coll->y11 && coll->y01 <= coll->y12) ||
        (coll->y02 >= coll->y11 && coll->y02 <= coll->y12))
        collision_y = 1;
    free(coll);
    if (collision_x == 1 && collision_y == 1)
        return (0);
    return (1);
}

void place_tower2(game_s *game, int id)
{
    order_t **orders = game->map->orders;
    sfVector2f pos = game->lvl_vars->cursor->pos;
    player_t *player = game->lvl_vars->player;
    lib_types_t *lib_types = game->lvl_vars->lib_types;
    int collision = 0;

    for (int i = 1; game->map->orders[i]->order != 0; i++)
        if (collision_entities
            (game->lvl_vars->player->tower_spectres[id],
            game->map->map_case[orders[i]->x][orders[i]->y]) == 1)
            collision = 1;
    if (collision == 0 && player->money >= lib_types->price_tower[id] &&
        not_in_ui(player->tower_spectres[id]) == 1) {
        sfMusic_play(game->beep);
        add_new_tower(game, id, pos);
        player->money -= lib_types->price_tower[id];
        game->lvl_vars->adress = 0;
    }
}

void place_tower(game_s *game)
{
    int id = -1;
    player_t *player = game->lvl_vars->player;

    for (int i = 0; i < 4; i++)
        if (game->lvl_vars->adress == &player->tower_buttons[i])
            id = i;
    if (id != -1) {
        place_tower2(game, id);
    }
}
