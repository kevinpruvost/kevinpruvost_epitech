/*
** EPITECH PROJECT, 2019
** utilities.c
** File description:
** outils
*/

#include "my.h"

int is_dir(char *name)
{
    struct stat *statbuf = malloc(sizeof(struct stat));

    if (statbuf == NULL)
        exit(84);
    if (name == NULL)
        return (0);
    if (stat(name, statbuf) == -1)
        return (0);
    if ((statbuf->st_mode & S_IFMT) == S_IFDIR)
        return (1);
    free(statbuf);
    return (0);
}

char *format(char *dir, char *file)
{
    char *new = str_add(str_add(dir, "/"), file);

    return (new);
}
