/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "castmania.h"

int normal_add(int a, int b)
{
    return (a + b);
}

int absolute_add(int a, int b)
{
    (a < 0) ? (a = -a) : (0);
    (b < 0) ? (b = -b) : (0);
    return (a + b);
}

void exec_add(addition_t *ope)
{
    int (*opes[2])(int a, int b) = {&normal_add, &absolute_add};
    integer_op_t dec = ope->add_op;

    dec.res = opes[ope->add_type](dec.a, dec.b);
    ope->add_op = dec;
}