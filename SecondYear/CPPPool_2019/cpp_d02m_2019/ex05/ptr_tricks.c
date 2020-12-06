/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "ptr_tricks.h"

#include <stdlib.h>

int get_array_nb_elem(const int *ptr1, const int *ptr2)
{
    int size = 0;

    if (ptr1 < ptr2) {
        for (const int *ptr = ptr1; ptr != ptr2; ++ptr)
            ++size;
    } else {
        for (const int *ptr = ptr1; ptr != ptr2; --ptr)
            ++size;
    }
    return (size);
}

whatever_t *get_struct_ptr(const int *member_ptr)
{
    long int adress = (long int)member_ptr;
    whatever_t * ptr;
    long int offset = (long int)(&ptr->member) - (long int)ptr;

    adress -= offset;
    ptr = (whatever_t *)(adress);

    return (ptr);
}