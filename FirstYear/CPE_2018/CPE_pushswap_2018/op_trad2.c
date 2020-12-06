/*
** EPITECH PROJECT, 2018
** op_trad2.c
** File description:
** rotate trad
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

void ra(list_t **list, int *ope)
{
    rotate(list);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("ra");
    } else {
        my_putstr(" ra");
    }
}

void rb(list_t **list, int *ope)
{
    rotate(list);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("rb");
    } else {
        my_putstr(" rb");
    }
}

void rr(list_t **list_a, list_t **list_b, int *ope)
{
    rotate(list_a);
    rotate(list_b);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("rr");
    } else {
        my_putstr(" rr");
    }
}
