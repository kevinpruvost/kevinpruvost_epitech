/*
** EPITECH PROJECT, 2019
** my_revlist.c
** File description:
** reverse list
*/

#include "my.h"

int my_rev_files(file_t **list)
{
    file_t *li;
    file_t *stock;
    file_t *stock_next;

    li = *list;
    stock = 0;
    while (li->next) {
        stock_next = li->next;
        li->next = stock;
        stock = li;
        li = stock_next;
    }
    li->next = stock;
    *list = li;
}

int my_rev_dir(dir_t **list)
{
    dir_t *li;
    dir_t *stock;
    dir_t *stock_next;

    li = *list;
    stock = 0;
    while (li->next) {
        stock_next = li->next;
        li->next = stock;
        stock = li;
        li = stock_next;
    }
    li->next = stock;
    *list = li;
}
