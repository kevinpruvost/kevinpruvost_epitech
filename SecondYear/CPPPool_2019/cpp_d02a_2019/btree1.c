/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "double_btree.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool double_btree_is_empty(double_btree_t tree)
{
    if (tree == NULL)
        return (true);
    return (false);
}

unsigned int double_btree_get_size(double_btree_t tree)
{
    int size = 0;

    if (tree == NULL)
        return (0);
    if (tree->left != NULL)
        size += double_btree_get_size(tree->left);
    if (tree->right != NULL)
        size += double_btree_get_size(tree->right);
    return (size + 1);
}

unsigned int double_btree_get_depth(double_btree_t tree)
{
    int size1 = 0;
    int size2 = 0;

    if (tree == NULL)
        return (0);
    if (tree->left != NULL)
        size1 = double_btree_get_depth(tree->left);
    if (tree->right != NULL)
        size2 = double_btree_get_depth(tree->right);
    if (size1 > size2)
        return (1 + size1);
    return (1 + size2);
}

bool double_btree_create_node(double_btree_t *rptr, double value)
{
    if (rptr == NULL)
        return (false);
    (*rptr == NULL) ? (*rptr = malloc(sizeof(doublebtree_node_t))) : (0);
    if (*rptr == NULL)
        return (false);
    (*rptr)->value = value;
    (*rptr)->left = NULL;
    (*rptr)->right = NULL;
    return (true);
}

bool double_btree_delete(double_btree_t *root_ptr)
{
    if (root_ptr == NULL || *root_ptr == NULL)
        return (false);

    if ((*root_ptr)->left != NULL)
        double_btree_delete(&((*root_ptr)->left));
    if ((*root_ptr)->right != NULL)
        double_btree_delete(&((*root_ptr)->right));
    free(*root_ptr);
    return (true);
}