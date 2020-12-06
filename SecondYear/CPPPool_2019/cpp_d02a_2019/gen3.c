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

void list_clear(list_t *fptr)
{
    if (*fptr != NULL) {
        list_clear(&((*fptr)->next));
        free(*fptr);
    }
}

void *list_get_elem_at_front(list_t list)
{
    if (list == NULL)
        return (0);
    return (list->value);
}

void *list_get_elem_at_back(list_t list)
{
    if (list == NULL)
        return (0);
    if (list->next == NULL)
        return (list_get_elem_at_front(list));
    return (list_get_elem_at_back(list->next));
}

void *list_get_elem_at_position(list_t list, unsigned int pos)
{
    if (list == NULL)
        return (0);
    if (pos == 0)
        return (list_get_elem_at_front(list));
    return (list_get_elem_at_back(list->next));
}

node_t *list_get_first_node_with_value(list_t list, void *value, \
value_comparator_t val_comp)
{
    if (list == NULL)
        return (NULL);
    if (val_comp(value, list->value) == 0)
        return (list);
    return (list_get_first_node_with_value(list->next, value, val_comp));
}