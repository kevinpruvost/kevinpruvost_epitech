/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "map.h"

#include <stddef.h>

static key_comparator_t key_cmpp = NULL;

unsigned int map_get_size(map_t map)
{
    return (list_get_size(map));
}

bool map_is_empty(map_t map)
{
    return (list_is_empty(map));
}

key_comparator_t key_cmp_container(bool store, key_comparator_t new_key_cmp)
{
    if (store)
        key_cmpp = new_key_cmp;
    return (key_cmpp);
}

int pair_comparator(void *first, void *second)
{
    if (first != NULL && second != NULL && key_cmpp != NULL) {
        return (key_cmpp(first, second));
    }
    return (84);
}