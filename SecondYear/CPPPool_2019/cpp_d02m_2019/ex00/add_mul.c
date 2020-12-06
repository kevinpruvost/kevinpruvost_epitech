/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include <stdio.h>

void add_mul_4param(int first, int second, int *sum, int *product)
{
    *sum = first + second;
    *product = first * second;
}

void add_mul_2param(int *first, int *second)
{
    int sum = (*first) + (*second);

    *second = (*first) * (*second);
    *first = sum;
}