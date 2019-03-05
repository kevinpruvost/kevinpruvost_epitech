/*
** EPITECH PROJECT, 2019
** data.c
** File description:
** where i configure data_t
*/

#include "my.h"

file_t *create_file(char *name)
{
    struct stat *statbuf = malloc(sizeof(struct stat));
    file_t *n_file = malloc(sizeof(file_t));

    n_file->t_name = name;
    n_file->name = malloc(sizeof(char) * (my_strlen(name) + 1));
    for (int i = 0, j = my_strlen(name) - 1; name[j] != '/'
    && name[j] != 0; i++, j--) {
        n_file->name[i] = name[j];
        n_file->name[i+1] = 0;
    }
    n_file->name = my_revstr(n_file->name);
    stat(name, statbuf);
    if (statbuf != NULL)
        n_file->statbuf = statbuf;
    n_file->time = correct_time(ctime(&statbuf->st_mtime));
    n_file->next = NULL;
    free(statbuf);
    return (n_file);
}

file_t *add_file(file_t *files, char *name)
{
    struct stat *statbuf = malloc(sizeof(struct stat));
    file_t *n_file = malloc(sizeof(file_t));
    file_t *initial_files = files;

    n_file->t_name = name;
    n_file->name = malloc(sizeof(char) * (my_strlen(name) + 1));
    for (int i = 0, j = my_strlen(name) - 1; name[j] != '/'
    && name[j] != 0; i++, j--) {
        n_file->name[i] = name[j];
        n_file->name[i+1] = 0;
    }
    n_file->name = my_revstr(n_file->name);
    stat(name, statbuf);
    n_file->time = correct_time(ctime(&statbuf->st_mtime));
    n_file->next = NULL;
    while (initial_files->next != NULL)
        initial_files = initial_files->next;
    initial_files->next = n_file;
    free(statbuf);
    return (files);
}

dir_t *add_dir(dir_t *dir, char *name, int mode)
{
    dir_t *nc = malloc(sizeof(dir_t));
    struct stat *statbuf = malloc(sizeof(struct stat));
    struct dirent *dp;
    dir_t *init = dir;
    DIR *pointer;

    nc = init_dir(nc, statbuf, name);
    pointer = opendir(name);
    if (pointer == NULL)
        return (NULL);
    dp = readdir(pointer);
    nc = process_dir(nc, mode, dp, pointer);
    if (nc->files != NULL)
        nc->files = sort_file_t(nc->files, mode);
    if (nc->sub != NULL)
        nc->sub = sort_dir_t(nc->sub, mode);
    while (init->next != NULL)
        init = init->next;
    init->next = nc;
    return (dir);
}

dir_t *create_dir(char *name, int mode)
{
    dir_t *dir = malloc(sizeof(dir_t));
    struct stat *statbuf = malloc(sizeof(struct stat));
    struct dirent *dp;
    DIR *pointer;

    dir = init_dir(dir, statbuf, name);
    pointer = opendir(name);
    if (pointer == NULL)
        return (NULL);
    dp = readdir(pointer);
    dir = process_dir(dir, mode, dp, pointer);
    if (dir->files != NULL)
        dir->files = sort_file_t(dir->files, mode);
    if (dir->sub != NULL)
        dir->sub = sort_dir_t(dir->sub, mode);
    return (dir);
}
