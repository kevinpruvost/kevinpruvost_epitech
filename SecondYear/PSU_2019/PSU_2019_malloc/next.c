/*
** EPITECH PROJECT, 2020
** next.c
** File description:
** next
*/

#include "libmy_malloc.h"

mem_t * next_ptr(mem_t * ptr)
{
    if (ptr == NULL)
        return NULL;
    if (ptr->next == false)
        return NULL;
    return (void *)(ptr + 1) + ptr->size;
}