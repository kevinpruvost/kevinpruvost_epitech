/*
** EPITECH PROJECT, 2018
** sorted.c
** File description:
** verify if the list is already sorted
*/

#include "include/my.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int tried(list_t **la, list_t **lb)
{
    list_t *base = *la;
    int sorted = 1;
    
    while (base->next != NULL) {
        if (base->value > base->next->value)
            sorted = 0;
        base = base->next;
    }
    return (sorted);
}
