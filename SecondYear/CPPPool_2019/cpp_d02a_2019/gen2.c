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

bool list_add_elem_at_position(list_t *fptr, void *el, unsigned int pos)
{
    if (fptr == NULL || *fptr == NULL)
        return (false);
    if (pos == 0)
        return (list_add_elem_at_front(fptr, el));
    if ((*fptr)->next != NULL)
        return (list_add_elem_at_position(&((*fptr)->next), el, pos-1));
    return (true);
}

bool list_del_elem_at_front(list_t *fptr)
{
    list_t to_delete;

    if (fptr == NULL || *fptr == NULL)
        return (false);
    to_delete = *fptr;
    *fptr = (*fptr)->next;
    free(to_delete);
    return (true);
}

bool list_del_elem_at_back(list_t *fptr)
{
    if (fptr == NULL || *fptr == NULL)
        return (false);
    if ((*fptr)->next == NULL)
        return (list_del_elem_at_front(fptr));
    return (list_del_elem_at_back(&((*fptr)->next)));
}

bool list_del_elem_at_position(list_t *fptr, unsigned int pos)
{
    if (fptr == NULL || *fptr == NULL)
        return (false);
    if (pos == 0)
        return (list_del_elem_at_front(fptr));
    if ((*fptr)->next != NULL)
        return (list_del_elem_at_position(&((*fptr)->next), pos-1));
    return (true);
}