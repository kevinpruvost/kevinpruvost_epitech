/*
** EPITECH PROJECT, 2018
** op_trad.c
** File description:
** operations traduced
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

void sa(list_t **list, int *ope)
{
    swap(list);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("sa");
    } else {
        my_putstr(" sa");
    }
}

void sb(list_t **list, int *ope)
{
    swap(list);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("sb");
    } else {
        my_putstr(" sb");
    }
}

void sc(list_t **list_a, list_t **list_b, int *ope)
{
    swap(list_a);
    swap(list_b);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("sc");
    } else {
        my_putstr(" sc");
    }
}

void pa(list_t **list_a, list_t **list_b, int *ope)
{
    push(list_b, list_a);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("pa");
    } else {
        my_putstr(" pa");
    }
}

void pb(list_t **list_a, list_t **list_b, int *ope)
{
    push(list_a, list_b);
    if (*ope == 0) {
        *ope = 1;
        my_putstr("pb");
    } else {
        my_putstr(" pb");
    }
}
