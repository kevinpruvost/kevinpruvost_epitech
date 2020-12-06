/*
** EPITECH PROJECT, 2018
** op_trad3.c
** File description:
** trad for reverse rotations
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/my.h"

void rra_v(list_t **la, list_t **lb)
{
    rotate_reverse(la);
    my_putstr("ra\n");
    my_putstr("list a : ");
    print_list(*la);
    my_putstr("list b : ");
    print_list(*lb);
    my_putstr("\n");
}

void rrb_v(list_t **list, int *ope)
{
    rotate_reverse(list);
    my_putstr("rrb\n");
    my_putstr("list b : ");
    print_list(*list);
    my_putstr("\n");
}
