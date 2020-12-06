/*
** EPITECH PROJECT, 2020
** read.c
** File description:
** read
*/

#include "nm.h"

static void print_line32(t_list32 * list)
{
    if (list->value == 0 && list->type != 'T' && list->type != 't')
        printf("%010c %s", list->type, list->name);
    else
        printf("%08x %c %s", list->value, list->type, list->name);
    printf("\n");
}

static void print_line64(t_list64 * list)
{
    if (list->value == 0 && list->type != 'T' && list->type != 't')
        printf("%018c %s", list->type, list->name);
    else
        printf("%016x %c %s", list->value, list->type, list->name);
    printf("\n");
}

int read32(nm_t * elf)
{
    for (long int nb = elf->list_len; nb >= 0; --nb) {
        print_line32(&(elf->sym_list32[nb]));
    }
    return EXIT_SUCCESS;
}

int read64(nm_t * elf)
{
    for (long int nb = elf->list_len; nb >= 0; --nb) {
        print_line64(&(elf->sym_list64[nb]));
    }
    return EXIT_SUCCESS;
}