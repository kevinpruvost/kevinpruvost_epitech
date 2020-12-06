/*
** EPITECH PROJECT, 2018
** second_main.c
** File description:
** main for multiple cases
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/my.h"

int second_main(int ac, char **av)
{
    list_t *list_a = write_in_list(list_a, av, ac);
    list_t *list_b = NULL;
    int ope = 0;

    selection_sorting(&list_a, &list_b, &ope);
    my_putchar('\n');
    free_list(list_a);
    return (0);
}

list_t *write_in_list_option(list_t *list_a, char **av, int ac)
{
    list_a = malloc(sizeof(list_t));
    list_a->value = my_atoi(av[2]);
    for (int i = 3; i < ac; i++) {
        add_list(my_atoi(av[i]), list_a);
    }
    return (list_a);
}

int option_main(int ac, char **av)
{
    list_t *list_a = write_in_list_option(list_a, av, ac);
    list_t *list_b = NULL;
    int ope = 0;

    selection_sorting_option(&list_a, &list_b, &ope);
    free_list(list_a);
    return (0);
}
