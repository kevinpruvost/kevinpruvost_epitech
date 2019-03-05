/*
** EPITECH PROJECT, 2019
** options2.c
** File description:
** options extension
*/

#include "my.h"

void print_l_dir(dir_t *dir, int size)
{
    struct stat *statbuf = malloc(sizeof(struct stat));

    stat(dir->t_name, statbuf);
    print_rights(statbuf);
    print_owners(statbuf, dir->time, size);
    my_putstr(dir->name);
    free(statbuf);
}

void print_l_file(file_t *dir, int size)
{
    struct stat *statbuf = malloc(sizeof(struct stat));

    stat(dir->t_name, statbuf);
    print_rights(statbuf);
    print_owners(statbuf, dir->time, size);
    my_putstr(dir->name);
    free(statbuf);
}

dir_t *reverse_all(dir_t *dir)
{
    dir_t *use = dir;

    while (use != NULL) {
        my_rev_files(&use->files);
        use = use->next;
    }
    use = dir;
    my_rev_dir(&dir);
    while (use != NULL) {
        if (use->sub != NULL)
            use->sub = reverse_all(dir->sub);
        use = use->next;
    }
    return (dir);
}
