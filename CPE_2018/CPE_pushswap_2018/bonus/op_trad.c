/*
** EPITECH PROJECT, 2018
** op_trad.c
** File description:
** operations traduced
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/my.h"

void pa_v(list_t **list_a, list_t **list_b, int *ope)
{
    push(list_b, list_a);
    my_putstr("pa\n");
    my_putstr("list a : ");
    print_list(*list_a);
    my_putstr("list b : ");
    print_list(*list_b);
    my_putstr("\n");
}

void pb_v(list_t **list_a, list_t **list_b, int *ope)
{
    push(list_a, list_b);
    my_putstr("pb\n");
    my_putstr("list a : ");
    print_list(*list_a);
    my_putstr("list b : ");
    print_list(*list_b);
    my_putstr("\n");
}
