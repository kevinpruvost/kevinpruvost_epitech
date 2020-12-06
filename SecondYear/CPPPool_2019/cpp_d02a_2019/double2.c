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

bool double_list_add_elem_at_position(double_list_t *fptr, \
double el, unsigned int pos)
{
    if (fptr == NULL || *fptr == NULL)
        return (false);
    if (pos == 0)
        return (double_list_add_elem_at_front(fptr, el));
    if ((*fptr)->next != NULL)
        return (double_list_add_elem_at_position(&((*fptr)->next), el, pos-1));
    return (true);
}

bool double_list_del_elem_at_front(double_list_t *fptr)
{
    double_list_t to_delete;

    if (fptr == NULL || *fptr == NULL)
        return (false);
    to_delete = *fptr;
    *fptr = (*fptr)->next;
    free(to_delete);
    return (true);
}

bool double_list_del_elem_at_back(double_list_t *fptr)
{
    if (fptr == NULL || *fptr == NULL)
        return (false);
    if ((*fptr)->next == NULL)
        return (double_list_del_elem_at_front(fptr));
    return (double_list_del_elem_at_back(&((*fptr)->next)));
}

bool double_list_del_elem_at_position(double_list_t *fptr, unsigned pos)
{
    if (fptr == NULL || *fptr == NULL)
        return (false);
    if (pos == 0)
        return (double_list_del_elem_at_front(fptr));
    if ((*fptr)->next != NULL)
        return (double_list_del_elem_at_position(&((*fptr)->next), pos-1));
    return (true);
}

double double_list_get_elem_at_front(double_list_t list)
{
    if (list == NULL)
        return (0);
    return (list->value);
}