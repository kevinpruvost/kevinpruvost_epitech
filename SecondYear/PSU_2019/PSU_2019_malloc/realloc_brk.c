/*
** EPITECH PROJECT, 2020
** realloc_brk
** File description:
** realloc_brk
*/

#include "libmy_malloc.h"

void *memcpy(void *, const void *, size_t);

void *realloc_ptr(void *ptr, long size, mem_t *baseBrk)
{
    while (baseBrk != NULL) {
        if (baseBrk + 1 == ptr && baseBrk->size >= size) {
            return (ptr);
        } else if (baseBrk + 1 == ptr) {
            void *newPtr = malloc(size);
            memcpy(newPtr, ptr, baseBrk->size);
            free(ptr);
            return (newPtr);
        }
        baseBrk = baseBrk->next;
    }
    return NULL;
}