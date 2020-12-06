/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "generic_list.h"

#include <stddef.h>
#include <stdlib.h>

bool list_del_node(list_t *front_ptr, node_t *node_ptr)
{
    if (front_ptr == NULL || *front_ptr == NULL || node_ptr == NULL)
        return (false);
    if (*front_ptr == node_ptr) {
        *front_ptr = (*front_ptr)->next;
        free(node_ptr);
        return (true);
    }
    return (list_del_node(&((*front_ptr)->next), node_ptr));
}