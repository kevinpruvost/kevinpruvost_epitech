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

unsigned int double_list_get_size(double_list_t list)
{
    if (list == NULL)
        return (0);
    return (1 + double_list_get_size(list->next));
}

bool double_list_is_empty(double_list_t list)
{
    if (list == NULL)
        return (true);
    return (false);
}

void double_list_dump(double_list_t list)
{
    if (list != NULL) {
        printf("%f\n", list->value);
        double_list_dump(list->next);
    }
}

bool double_list_add_elem_at_front(double_list_t *front_ptr, double elem)
{
    double_list_t new_node = malloc(sizeof(doublelist_node_t));

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

bool double_list_add_elem_at_back(double_list_t *front_ptr, double elem)
{
    double_list_t new_node = malloc(sizeof(doublelist_node_t));
    double_list_t ptr;

    if (new_node == NULL)
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