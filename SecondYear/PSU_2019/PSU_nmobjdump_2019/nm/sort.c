/*
** EPITECH PROJECT, 2020
** sort.c
** File description:
** sort
*/

#include "nm.h"

#include <string.h>

static int cmp_names2(char * name1, char *name2, int i1, int i2)
{
    int ret = 0;

    (name1[i1] == 0 && name2[i2] == 0) ? ret = 0 : 0;
    (name1[i1] == 0 && name2[i2] != 0) ? ret = -1 : 0;
    (name1[i1] != 0 && name2[i2] == 0) ? ret = 1 : 0;
    return ret;
}

static int cmp_names(char * name1, char *name2)
{
    int i1 = 0;
    int i2 = 0;
    char c1 = 0;
    char c2 = 0;

    while (strchr("@_.", name1[i1])) ++i1;
    while (strchr("@_.", name2[i2])) ++i2;
    for (; name1[i1] != 0 && name2[i2] != 0; ++i1, ++i2) {
        while (strchr("@_.", name1[i1])) ++i1;
        while (strchr("@_.", name2[i2])) ++i2;
        c1 = (name1[i1] >= 'A' && name1[i1] <= 'Z') ?
    name1[i1] + 'a' - 'A' : name1[i1];
        c2 = (name2[i2] >= 'A' && name2[i2] <= 'Z') ?
    name2[i2] + 'a' - 'A' : name2[i2];
        if (c1 > c2 || c1 < c2)
            return (c1 > c2) ? 1 : -1;
    }
    return cmp_names2(name1, name2, i1, i2);
}

static void swap(void * t1, void * t2, char c)
{
    t_list32 tmp32;
    t_list64 tmp64;

    if (c == 32) {
        memcpy(&tmp32, t1, sizeof(t_list32));
        memcpy(t1, t2, sizeof(t_list32));
        memcpy(t2, &tmp32, sizeof(t_list32));
    } else if (c == 64) {
        memcpy(&tmp64, t1, sizeof(t_list64));
        memcpy(t1, t2, sizeof(t_list64));
        memcpy(t2, &tmp64, sizeof(t_list64));
    }
}

int sort32(nm_t * elf)
{
    for (int i = 0; i < elf->list_len; ++i) {
        if (cmp_names(elf->sym_list32[i].name, elf->sym_list32[i+1].name) < 0) {
            swap(&(elf->sym_list32[i]), &(elf->sym_list32[i+1]), 32);
            return sort32(elf);
        }
    }
    return EXIT_SUCCESS;
}

int sort64(nm_t * elf)
{
    for (int i = 0; i < elf->list_len; ++i) {
        if (cmp_names(elf->sym_list64[i].name, elf->sym_list64[i+1].name) < 0) {
            swap(&(elf->sym_list64[i]), &(elf->sym_list64[i+1]), 64);
            return sort64(elf);
        }
    }
    return EXIT_SUCCESS;
}