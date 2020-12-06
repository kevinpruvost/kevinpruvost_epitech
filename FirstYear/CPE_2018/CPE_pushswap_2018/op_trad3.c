/*
** EPITECH PROJECT, 2018
** op_trad3.c
** File description:
** trad for reverse rotations
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

void rra(list_t **list, int *ope)
{
    rotate_reverse(list);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("rra");
    } else {
        my_putstr(" rra");
    }
}

void rrb(list_t **list, int *ope)
{
    rotate_reverse(list);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("rrb");
    } else {
        my_putstr(" rrb");
    }
}

void rrr(list_t **list_a, list_t **list_b, int *ope)
{
    rotate_reverse(list_a);
    rotate_reverse(list_b);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("rrr");
    } else {
        my_putstr(" rrr");
    }
}
