/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "double_list.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

double double_list_get_elem_at_back(double_list_t list)
{
    if (list == NULL)
        return (0);
    if (list->next == NULL)
        return (double_list_get_elem_at_front(list));
    return (double_list_get_elem_at_back(list->next));
}

double double_list_get_elem_at_position(double_list_t list, unsigned int pos)
{
    if (list == NULL)
        return (0);
    if (pos == 0)
        return (double_list_get_elem_at_front(list));
    return (double_list_get_elem_at_position(list->next, pos - 1));
}

doublelist_node_t *double_list_get_first_node_with_value(double_list_t list, \
double value)
{
    if (list == NULL)
        return (NULL);
    if (list->value == value)
        return (list);
    return (double_list_get_first_node_with_value(list, value));
}