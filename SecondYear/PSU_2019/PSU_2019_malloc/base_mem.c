/*
** EPITECH PROJECT, 2020
** base_mem.c
** File description:
** to counter the norm
*/

#include "libmy_malloc.h"

mem_t *base_mem(mem_t *mem)
{
    static mem_t *baseMem = NULL;

    if (mem != GET)
        baseMem = mem;
    return baseMem;
}

int getmpagesize(void)
{
    static int pagesize = 0;

    if (pagesize == 0)
        pagesize = 2 * getpagesize();
    return (pagesize);
}