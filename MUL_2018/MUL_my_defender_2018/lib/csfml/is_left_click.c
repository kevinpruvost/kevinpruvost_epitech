/*
** EPITECH PROJECT, 2019
** is_left_click.c
** File description:
** a left click is clicking ?
*/

#include "my.h"

int is_left_click(sfEvent event, game_obj *obj1, game_obj *obj2)
{
    if (collision_cursor(obj1, obj2) == 1 &&
        event.type == sfEvtMouseButtonReleased &&
        event.mouseButton.button == sfMouseLeft)
        return (1);
    return (0);
}
