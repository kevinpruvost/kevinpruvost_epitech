/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "map.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

bool map_create_elem(map_t *map_ptr, void *key, void *value)
{
    size_t size = sizeof(key) + sizeof(pair_t) + sizeof(value);
    pair_t *pair = malloc(size);
    map_t map = malloc(sizeof(node_t) + size);

    printf("%d, %d\n", sizeof(map_t), sizeof(node_t));

    if (map == NULL || pair == NULL)
        return (false);
    pair->key = key;
    pair->value = value;
    map->value = pair;
    map->next = NULL;
    *map_ptr = map;
    return (true);
}

bool map_add_elem(map_t *map_ptr, void *key, void *value, \
key_comparator_t key_cmp)
{
    pair_t *pair = (*map_ptr != NULL) ? ((*map_ptr)->value) : (0);

    if (map_ptr == NULL || key == NULL || value == NULL)
        return (false);
    if (*map_ptr == NULL)
        return (map_create_elem(map_ptr, key, value));
    if (key_cmp(pair->key, key) == 0) {
        pair->value = value;
        (*map_ptr)->value = pair;
        return (true);
    }
    return (map_add_elem((&(*map_ptr)->next), key, value, key_cmp));
}

bool map_del_elem2(map_t *map_ptr, void *key, key_comparator_t key_cmp)
{
    pair_t *pair;
    map_t map;

    pair = (*map_ptr)->value;
    if (key_cmp(pair->key, key) == 0) {
        map = *map_ptr;
        *map_ptr = map->next;
        free(map);
        return (true);
    }
    return (map_del_elem((&(*map_ptr)->next), key, key_cmp));
}

bool map_del_elem(map_t *map_ptr, void *key, key_comparator_t key_cmp)
{
    pair_t *pair;
    map_t map;

    if (map_ptr == NULL || *map_ptr == NULL || key == NULL)
        return (false);
    if ((*map_ptr)->next != NULL) {
        pair = (*map_ptr)->next->value;
        if (key_cmp(pair->key, key) == 0) {
            map = (*map_ptr)->next;
            (*map_ptr)->next = (*map_ptr)->next->next;
            free(map);
            return (true);
        }
    }
    return (map_del_elem2(map_ptr, key, key_cmp));
}

void *map_get_elem(map_t map, void *key, key_comparator_t key_cmp)
{
    pair_t *pair;

    if (map == NULL || key == NULL)
        return (NULL);
    pair = map->value;
    if (key_cmp(pair->key, key) == 0)
        return (pair->value);
    return (map_get_elem(map->next, key, key_cmp));
}