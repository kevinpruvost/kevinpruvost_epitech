/*
** EPITECH PROJECT, 2018
** op_trad2.c
** File description:
** rotate trad
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/my.h"

void ra_v(list_t **la, list_t **lb)
{
    rotate(la);
    my_putstr("ra\n");
    my_putstr("list a : ");
    print_list(*la);
    my_putstr("list b : ");
    print_list(*lb);
    my_putstr("\n");
}

void rb_v(list_t **list, int *ope)
{
    rotate(list);
    my_putstr("rb\n");
    my_putstr("list b : ");
    print_list(*list);
    my_putstr("\n");
}

void rr_v(list_t **list_a, list_t **list_b, int *ope)
{
    rotate(list_a);
    rotate(list_b);
    my_putstr("rr\n");
    my_putstr("list a : ");
    print_list(*list_a);
    my_putstr("list b : ");
    print_list(*list_b);
    my_putstr("\n");
}
