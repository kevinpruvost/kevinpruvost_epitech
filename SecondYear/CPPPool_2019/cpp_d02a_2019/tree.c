/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "tree_traversal.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

bool tree_is_empty(tree_t tree)
{
    if (tree == NULL)
        return (true);
    return (false);
}

void tree_node_dump(tree_node_t *tree_node, dump_func_t dump_func)
{
    if (tree_node == NULL)
        return;
    dump_func(tree_node->data);
    list_t list = tree_node->children;
    while (list != NULL) {
        tree_node_dump(list->value, dump_func);
        list = list->next;
    }
}

bool init_tree(tree_t *tree_ptr, void *data)
{
    tree_t obj;

    if (tree_ptr == NULL)
        return (false);
    obj = malloc(sizeof(tree_node_t) + sizeof(data));
    if (obj == NULL)
        return (false);
    obj->data = data;
    obj->parent = NULL;
    obj->children = NULL;
    *tree_ptr = obj;
    return (true);
}

tree_node_t *tree_add_child(tree_node_t *tree_node, void *data)
{
    tree_node_t *obj = malloc(sizeof(tree_node_t) + sizeof(data));
    list_t list;

    if (obj == NULL)
        return (NULL);
    obj->data = data;
    obj->parent = tree_node;
    obj->children = NULL;
    list = tree_node->children;
    list_add_elem_at_back(&list, obj);
    tree_node->children = list;
    return (obj);
}

bool tree_destroy(tree_t *tree_ptr)
{
    if (tree_ptr == NULL)
        return (false);
    if ((*tree_ptr)->children == NULL)
        list_clear(&(*tree_ptr)->children);
    free(*tree_ptr);
    *tree_ptr = NULL;
    return (true);
}