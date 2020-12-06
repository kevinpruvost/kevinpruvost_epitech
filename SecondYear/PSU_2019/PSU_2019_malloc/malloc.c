/*
** EPITECH PROJECT, 2020
** malloc
** File description:
** malloc
*/

#include "libmy_malloc.h"

#include <string.h>

void free(void *ptr)
{
    if (ptr == NULL || base_mem(GET) == NULL)
        return;

    free_mem(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
    void *dest;

    if ((dest = malloc(nmemb * size)) == NULL)
        return (NULL);
    memset(dest, 0, nmemb * size);
    return (dest);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return (realloc(ptr, nmemb * size));
}

void *realloc(void *ptr, size_t size)
{
    size = resize_power(size);
    if (ptr == NULL)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    if (base_mem(GET) == NULL)
        return (NULL);
    return (realloc_ptr(ptr, size, base_mem(GET)));
}

void *malloc(size_t size)
{
    void *cell;

    if (size == 0)
        return NULL;

    size = resize_power(size);

    if (base_mem(GET) == NULL) {
        base_mem(init_mem(size));
        return (base_mem(GET) + 1);
    } else {
        cell = add_mem(size);
        return (cell + sizeof(mem_t));
    }
}