/*
** EPITECH PROJECT, 2019
** tower_infos.c
** File description:
** tower infos
*/

#include "my.h"

void policies_size_tinfos(text_obj *tower_infos[5])
{
    for (int i = 0; i < 5; i++)
        sfText_setCharacterSize(tower_infos[i]->text, 28);
}

text_obj *create_tower_infos(text_obj *tower_infos[5], text_obj *no_tower_info)
{
    sfVector2f pos = {15, 800};
    sfColor cl = {50, 255, 50, 255};
    sfVector2f scale = {1, 1};

    tower_infos[0] = create_text_obj("Type : ", scale, pos, cl);
    pos.y += 30;
    tower_infos[1] = create_text_obj("Level : ", scale, pos, cl);
    pos.y += 30;
    tower_infos[2] = create_text_obj("Damages : ", scale, pos, cl);
    no_tower_info = create_text_obj
        ("Select a placed tower", scale, pos, cl);
    pos.y += 30;
    tower_infos[4] = create_text_obj("Attack speed : ", scale, pos, cl);
    pos.y += 30;
    tower_infos[3] = create_text_obj("Range : ", scale, pos, cl);
    policies_size_tinfos(tower_infos);
    return (no_tower_info);
}
