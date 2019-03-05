/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main functions
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

list_t *add_list(int value, list_t *list)
{
    list_t *new_list = list;
    list_t *new_cell = malloc(sizeof(list_t));

    while (new_list->next != NULL) {
        new_list = new_list->next;
    }
    new_cell->value = value;
    new_list->next = new_cell;
    return (list);
}

list_t *write_in_list(list_t *list_a, char **av, int ac)
{
    list_a = malloc(sizeof(list_t));
    list_a->value = my_atoi(av[1]);
    for (int i = 2; i < ac; i++) {
        add_list(my_atoi(av[i]), list_a);
    }
    return (list_a);
}

void free_list(list_t *list)
{
    list_t *to_free;

    while (list->next != NULL) {
        to_free = list;
        list = list->next;
        free(to_free);
    }
    free(list);
}

int main(int ac, char **av)
{
    int nb = ac;
    list_t *list_a = write_in_list(list_a, av, ac);
    list_t *list_b = NULL;
    int ope = 0;

    if (tried(&list_a, &list_b) == 0) {
        selection_sorting(&list_a, &list_b, &ope);
    }
    my_putchar('\n');
    free_list(list_a);
    return (0);
}
