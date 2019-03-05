/*
** EPITECH PROJECT, 2019
** is_file.c
** File description:
** check if a file is a file or not
*/

#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>

int is_reg_file(char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
