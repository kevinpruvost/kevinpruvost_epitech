/*
** EPITECH PROJECT, 2018
** insertion_sorting.c
** File description:
** sort by insertion
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

int measure(list_t *la)
{
    int length = 1;
    list_t *base = la;

    while (la->next != NULL) {
        la = la->next;
        length++;
    }
    la = base;
    return (length);
}

int check(list_t **la)
{
    list_t *base = *la;
    int	sorted = 0;

    while (base->next != NULL) {
        if (base->value > base->next->value)
            sorted++;
        base = base->next;
    }
    base = *la;
    return (sorted);
}

void take_base(list_t **la, int *ope)
{
    list_t *base = *la;
    list_t *lowest = *la;
    int nb = 0;

    for (int i = 0; base != NULL; base = base->next, i++) {
        if (base->value < lowest->value) {
            lowest = base;
            nb = i;
        }
    }
    my_put_nbr(lowest->value);
    for (int i = 0; *la != lowest; i++)
        ra(la, ope);
}

void insertion_sorting(list_t **la, list_t **lb, int *ope)
{
    list_t *reset = *la;
    int sorted = 1;
    int length = measure(*la);
    int i = 1;

    take_base(la, ope);
    reset = *la;
    for (; sorted > 0;) {
        for (; (*la)->value <= (*la)->next->value; ra(la, ope));
        pb(la, lb, ope);
        for (; (*lb)->value <= (*la)->value; ra(la, ope));
        ra(la, ope);
        pa(la, lb, ope);
        while (*la != reset)
            ra(la, ope);
        sorted = check(la);
    }
}
