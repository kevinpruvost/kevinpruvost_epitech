    /*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "generic_list.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

unsigned int list_get_size(list_t list)
{
    if (list == NULL)
        return (0);
    return (1 + list_get_size(list->next));
}

bool list_is_empty(list_t list)
{
    if (list == NULL)
        return (true);
    return (false);
}

void list_dump(list_t list, value_displayer_t val_disp)
{
    if (list != NULL) {
        val_disp(list->value);
        list_dump(list->next, val_disp);
    }
}

bool list_add_elem_at_front(list_t *front_ptr, void *elem)
{
    list_t new_node = malloc(sizeof(node_t) + sizeof(elem));

    if (new_node == NULL)
        return (false);
    new_node->value = elem;
    new_node->next = NULL;
    if (*front_ptr == NULL) {
        *front_ptr = new_node;
        return (true);
    }
    new_node->next = *front_ptr;
    *front_ptr = new_node;
    return (true);
}

bool list_add_elem_at_back(list_t *front_ptr, void *elem)
{
    list_t new_node = malloc(sizeof(node_t) + sizeof(elem));
    list_t ptr;

    if (front_ptr == NULL || new_node == NULL)
        return (false);
    new_node->value = elem;
    new_node->next = NULL;
    if (*front_ptr == NULL) {
        *front_ptr = new_node;
        return (true);
    }
    ptr = *front_ptr;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = new_node;
    return (true);
}