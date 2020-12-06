/*
** EPITECH PROJECT, 2020
** pre_open.c
** File description:
** pre open
*/

#include "nm.h"

int pre_open(const char * filename, int * fd, bool multiple, nm_t * elf)
{
    elf->filename = filename;
    *fd = open(filename, O_RDONLY);
    if (*fd == -1) {
        fprintf(stderr, "my_nm: '%s': No such file\n", filename);
        return EXIT_FAILURE;
    }
    if (multiple == true) {
        printf("\n%s:\n", filename);
    }
    return EXIT_SUCCESS;
}