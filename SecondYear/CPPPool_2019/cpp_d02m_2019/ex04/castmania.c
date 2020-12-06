/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "castmania.h"

#include <stdio.h>

void display_div(division_t * div)
{
    decimale_op_t *dec;
    integer_op_t *nit;

    if (div->div_type == INTEGER) {
        nit = div->div_op;
        printf("%d\n", nit->res);
    }
    if (div->div_type == DECIMALE) {
        dec = div->div_op;
        printf("%f\n", dec->res);
    }
}

void exec_operation(instruction_type_t instruction_type, void *data)
{
    instruction_t *inst = data;
    division_t *div;
    addition_t *add;

    if (data == NULL)
        return;
    if (instruction_type == ADD_OPERATION) {
        add = inst->operation;
        exec_add(add);
        if (inst->output_type == VERBOSE)
            printf("%d\n", add->add_op.res);
    } else if (instruction_type == DIV_OPERATION) {
        div = inst->operation;
        exec_div(div);
        if (inst->output_type == VERBOSE)
            display_div(div);
    }
}

void exec_instruction(instruction_type_t instruction_type, void *data)
{
    int *nb;
    float *flnb;

    if (data == NULL)
        return;
    if (instruction_type == PRINT_INT) {
        nb = data;
        printf("%d\n", *nb);
    } else if (instruction_type == PRINT_FLOAT) {
        flnb = data;
        printf("%f\n", *flnb);
    } else
        exec_operation(instruction_type, data);
}