/*
** EPITECH PROJECT, 2020
** add_mem.c
** File description:
** add mem
*/

#include "libmy_malloc.h"

void add_empty_mem(mem_t * tmp, size_t size)
{
    mem_t *new_cell;
    long base = tmp->size;

    if ((long int)(size) - MEM_T_SIZE > 0) {
        tmp->size -= size;
        tmp->size = resize_power(tmp->size);
        if (tmp->size == base)
            return;
        new_cell = ((void *)(tmp + 1) + tmp->size);
        new_cell->size = base - tmp->size - MEM_T_SIZE;
        new_cell->next = tmp->next;
        tmp->next = new_cell;
        new_cell->freed = false;
        free(new_cell + 1);
    }
}

void * add_mem2(const long size, mem_t * tmp)
{
    mem_t *new_mem;
    long int overSize = resize(size + MEM_T_SIZE);

    new_mem = ((void *)(tmp + 1) + tmp->size);
    if (my_sbrk(overSize) == (void *)-1)
        return NULL;
    new_mem->size = size;
    new_mem->freed = false;
    overSize -= (size + MEM_T_SIZE);
    if (overSize <= MEM_T_SIZE)
        new_mem->next = NULL;
    else {
        new_mem->next = ((void *)(new_mem + 1) + new_mem->size);
        new_mem->next->freed = true;
        new_mem->next->size = overSize - MEM_T_SIZE;
        new_mem->next->next = NULL;
    }
    tmp->next = new_mem;
    return (new_mem);
}

void * add_mem(const long size)
{
    mem_t *tmp = base_mem(GET);
    mem_t *bestFit = NULL;

    if (tmp == NULL)
        return (NULL);
    while (tmp != NULL && tmp->next != NULL) {
        if (tmp->freed == true && tmp->size >= size &&
            (bestFit == NULL || bestFit->size > tmp->size))
            bestFit = tmp;
        tmp = tmp->next;
    }
    if (bestFit != NULL) {
        bestFit->freed = false;
        add_empty_mem(bestFit, bestFit->size - size);
        return (bestFit);
    }
    return (add_mem2(size, tmp));
}
