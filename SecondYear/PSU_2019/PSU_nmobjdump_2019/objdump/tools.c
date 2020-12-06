/*
** EPITECH PROJECT, 2020
** isarfile.c
** File description:
** isarfile
*/

#include "objdump.h"

#include <string.h>

bool isarfile(int fd)
{
    char magic_ar[SARMAG];

    if (read(fd, magic_ar, SARMAG) != SARMAG)
        return (false);
    if (strncmp(magic_ar, ARMAG, SARMAG))
        return (false);
    return (true);
}