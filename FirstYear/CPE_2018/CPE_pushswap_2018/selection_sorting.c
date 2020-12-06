/*
** EPITECH PROJECT, 2018
** selection_sorting.c
** File description:
** sorting by selection
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

void selection_sorting2(list_t **la, int *ope, int nbr, int rb)
{
    if (rb > nbr / 2) {
        for (int i = 0; i < nbr - rb; i++)
            rra(la, ope);
    } else {
        for (int i = 0; i < rb; i++)
            ra(la, ope);
    }
}

void selection_sorting(list_t **la, list_t **lb, int *ope)
{
    list_t *lowest_number = NULL;
    list_t *reset = *la;
    int nbr = 0;
    int rb = 0;

    for (int i = 0; *la != NULL; i++) {
        reset = *la;
        lowest_number = *la;
        for (nbr = 0, rb = 0; *la != NULL; *la = (*la)->next, nbr++) {
            if ((*la)->value < lowest_number->value) {
                lowest_number = *la;
                rb = nbr;
            }
        }
        *la = reset;
        selection_sorting2(la, ope, nbr, rb);
        pb(la, lb, ope);
    }
    for (; *lb != NULL;)
        pa(la, lb, ope);
}
