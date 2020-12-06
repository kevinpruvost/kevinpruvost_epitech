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

double double_btree_get_max_value(double_btree_t root_ptr)
{
    double res1 = 0;
    double res2 = 0;
    double ret = 0;

    if (root_ptr == NULL)
        return (0);
    if (root_ptr->left != NULL)
        res1 = double_btree_get_max_value(root_ptr->left);
    if (root_ptr->right != NULL)
        res2 = double_btree_get_max_value(root_ptr->right);
    ret = (res1 > res2) ? (res1) : (res2);
    return ((root_ptr->value > ret) ? (root_ptr->value) : (ret));
}

double double_btree_get_min_value(double_btree_t root_ptr)
{
    double res1 = 0;
    double res2 = 0;
    double ret = 0;

    if (root_ptr->left == NULL && root_ptr->right == NULL)
        return (root_ptr->value);
    if (root_ptr->left != NULL) {
        res1 = double_btree_get_min_value(root_ptr->left);
        ret = res1;
    }
    if (root_ptr->right != NULL) {
        res2 = double_btree_get_min_value(root_ptr->right);
        ret = res2;
    }
    if (root_ptr->right != NULL && root_ptr->left != NULL)
        ret = (res1 < res2) ? (res1) : (res2);
    return ((root_ptr->value < ret) ? (root_ptr->value) : (ret));
}