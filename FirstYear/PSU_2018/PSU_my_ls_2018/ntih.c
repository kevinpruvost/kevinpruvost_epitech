/*
** EPITECH PROJECT, 2019
** ntih.c
** File description:
** name type inode hard links
*/

#include "my.h"

char *info_file_name(char *file_name)
{
    int pt = 0;
    char *name = malloc(sizeof(char) * my_strlen(file_name));

    for (int i = 0; file_name[i] != 0; i++)
        if (file_name[i] == '/' && file_name[i+1] != 0)
            pt = i + 1;
    for (int i = pt, j = 0; file_name[i] != 0 && file_name[i] != '.'; i++, j++)
        name[j] = file_name[i];
    return (name);
}
