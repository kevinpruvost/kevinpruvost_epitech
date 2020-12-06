/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "tree_traversal.h"

#include <stddef.h>
#include <stdio.h>

void tree_traversal(tree_t tree, container_t *container, \
dump_func_t dum)
{
    list_t list = NULL;

    if (tree == NULL)
        return;
    list = tree->children;
    while (list != NULL) {
        container->push_func(container->container, list->value);
        list = list->next;
    }
    dum(tree->data);
    tree_traversal(container->pop_func(container->container), container, dum);
}