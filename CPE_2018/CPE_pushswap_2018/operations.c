/*
** EPITECH PROJECT, 2018
** operations.c
** File description:
** operations allowed in pushswap
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

int swap(list_t **list)
{
    list_t *first_list = *list;
    list_t *last_list;

    if ((*list)->next == NULL)
        return (0);
    while ((*list)->next->next != NULL) {
        *list = (*list)->next;
    }
    last_list = (*list)->next;
    last_list->next = first_list->next;
    (*list)->next = first_list;
    first_list->next = NULL;

    *list = last_list;
}

void push(list_t **list_a, list_t **list_b)
{
    list_t *new_list_a;
    list_t *new_list_b;

    new_list_a = *list_a;
    *list_a = (*list_a)->next;
    new_list_b = new_list_a;
    new_list_b->next = *list_b;
    *list_b = new_list_b;
}

int rotate_reverse(list_t **list)
{
    list_t *first_cell = *list;
    list_t *last_cell;

    while ((*list)->next->next != NULL) {
        *list =	(*list)->next;
    }
    last_cell = (*list)->next;
    last_cell->next = first_cell;

    (*list)->next = NULL;
    (*list) = last_cell;
}

int rotate(list_t **list)
{
    list_t *first_cell = *list;
    list_t *last_cell;

    while ((*list)->next != NULL) {
        *list = (*list)->next;
    }
    last_cell = *list;
    last_cell = first_cell->next;
    first_cell->next = NULL;

    (*list)->next = first_cell;
    *list = last_cell;
}

int print_list(list_t *list)
{
    if (list == NULL) {
        my_putchar('\n');
        return (0);
    }
    while (list->next != NULL && list != NULL) {
        my_put_nbr(list->value);
        my_putchar(' ');
        list = list->next;
    }
    my_put_nbr(list->value);
    my_putchar('\n');
}
