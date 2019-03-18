/*
** EPITECH PROJECT, 2019
** display_tower_info.c
** File description:
** display info for the towers
*/

#include "my.h"

void create_string_tower_infos(char *strs[5], tower_t *tower)
{
    int type = tower->type;

    (type == DMG) ? (strs[0] = "Fiona, DMG") : (0);
    (type == DOT) ? (strs[0] = "Shrek, DOT") : (0);
    (type == SLOW) ? (strs[0] = "Donkey, SLOW") : (0);
    (type == HEAVY) ? (strs[0] = "Dragon, HEAVY") : (0);
    strs[1] = my_getnbr(tower->lvl);
    strs[2] = float_to_s(tower->damage);
    strs[3] = float_to_s(tower->range);
    strs[4] = float_to_s(1 / (tower->atk_speed / 3));
}

void mod_dot_info(char *strs[5], tower_t *tower)
{
    strs[2] = str_add(strs[2], " (+");
    strs[2] = str_add(strs[2], my_getnbr(tower->damage * 3.75));
    strs[2] = str_add(strs[2], ")");
}

void mod_tower_infos(game_s *game, tower_t *tower)
{
    char *strs[5];

    create_string_tower_infos(strs, tower);
    sfText_setString(game->lvl_vars->tower_infos[0]->text,
    str_add("Type : ", strs[0]));
    sfText_setString(game->lvl_vars->tower_infos[1]->text,
    str_add("Level : ", strs[1]));
    if (tower->type == DOT)
        mod_dot_info(strs, tower);
    sfText_setString(game->lvl_vars->tower_infos[2]->text,
    str_add("Damages : ", strs[2]));
    sfText_setString(game->lvl_vars->tower_infos[3]->text,
    str_add("Range : ", strs[3]));
    sfText_setString(game->lvl_vars->tower_infos[4]->text,
    str_add(str_add("Attack speed : ", strs[4]), " / sec"));
}

void render_tower_infos(game_s *game)
{
    for (int i = 0; i < 5; i++)
        sfRenderWindow_drawText
        (game->win,
        game->lvl_vars->tower_infos[i]->text, NULL);
}

void display_tower_info(game_s *game)
{
    tower_t *towers = game->lvl_vars->towers;
    int show = 0;

    for (; towers != NULL; towers = towers->next) {
        if (game->lvl_vars->adress == &towers->props) {
            mod_tower_infos(game, towers);
            show = 1;
            render_tower_infos(game);
        }
    }
    if (show == 0)
        sfRenderWindow_drawText
        (game->win,
        game->lvl_vars->no_tower_info->text, NULL);
}
