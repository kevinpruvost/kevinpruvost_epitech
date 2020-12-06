/*
** EPITECH PROJECT, 2020
** my_sbrk.c
** File description:
** sbrk
*/

#include "libmy_malloc.h"

#include <stdio.h>

int verify_length(void)
{
    mem_t *tmp = base_mem(GET);
    long total = 0;

    while (tmp != NULL) {
        total += MEM_T_SIZE;
        total += tmp->size;
        tmp = tmp->next;
    }
    return false;
}

long resize(long size)
{
    long mult = getmpagesize();
    long res = mult;

    while (size > res)
        res += mult;
    return res;
}

long resize_power(long size)
{
    long res = 8;

    if (size == 0)
        return (0);

    while (size > res)
        res *= 2;
    return (res);
}

void * my_sbrk(long size)
{
    return (sbrk(size));
}

int my_brk(void *ptr)
{
    return (brk(ptr));
}