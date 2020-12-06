/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "castmania.h"

#include <stdio.h>

int integer_div(int a, int b)
{
    if (b == 0)
        return (0);
    return (a/b);
}

float decimale_div(int a, int b)
{
    float c;

    if (b == 0)
        return (0);

    c = (float)a / (float)b;
    return (c);
}

void exec_div(division_t *ope)
{
    decimale_op_t *dec;
    integer_op_t *nit;

    if (ope->div_type == DECIMALE) {
        dec = ope->div_op;
        dec->res = decimale_div(dec->a, dec->b);
        ope->div_op = dec;
    }
    else if (ope->div_type == INTEGER) {
        nit = ope->div_op;
        nit->res = integer_div(nit->a, nit->b);
        ope->div_op = nit;
    }
}