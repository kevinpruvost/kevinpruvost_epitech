/*
** EPITECH PROJECT, 2020
** mem_struct.c
** File description:
** mem struct woulah
*/

#include "libmy_malloc.h"

#include <stdlib.h>

mem_t *init_mem(const long size)
{
    mem_t *struc = NULL;
    long overSize = resize(size + MEM_T_SIZE);

    base_mem(my_sbrk(overSize));
    if (base_mem(GET) == (void *)-1)
        return NULL;
    struc = base_mem(GET);
    struc->size = size;
    struc->freed = false;
    overSize -= size + MEM_T_SIZE;
    if (overSize <= MEM_T_SIZE)
        struc->next = NULL;
    else {
        struc->next = ((void *)(struc + 1) + struc->size);
        struc->next->freed = true;
        struc->next->size = overSize - MEM_T_SIZE;
        struc->next->next = NULL;
    }
    return (struc);
}

void free_mem(void *adress)
{
    mem_t *tmp = (void *)adress - MEM_T_SIZE;

    if (tmp->freed == false) {
        tmp->freed = true;
        free_brk(base_mem(GET));
        return;
    }
    abort();
}