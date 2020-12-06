/*
** EPITECH PROJECT, 2018
** selection_sorting_option.c
** File description:
** selection sorting for -v
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/my.h"

void selection_sorting2_option(list_t **la, list_t **lb, int nbr, int rb)
{
    if (rb > nbr / 2) {
        for (int i = 0; i < nbr - rb; i++)
            rra_v(la, lb);
    } else {
        for (int i = 0; i < rb; i++)
            ra_v(la, lb);
    }
}

void selection_sorting_option(list_t **la, list_t **lb, int *ope)
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
        selection_sorting2_option(la, lb, nbr, rb);
        pb_v(la, lb, ope);
    }
    for (; *lb != NULL;)
        pa_v(la, lb, ope);
}
