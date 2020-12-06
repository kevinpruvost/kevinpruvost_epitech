/*
** EPITECH PROJECT, 2019
** sort_dir_t2.c
** File description:
** sort 2
*/

#include "my.h"

dir_t *comp_exchange_dir(dir_t *dir1, dir_t *dir2)
{
    dir2 = dir2->next;
    dir1->next = dir2->next;
    dir2->next = dir1;
    return (dir2);
}

file_t *comp_exchange_file(file_t *dir1, file_t *dir2)
{
    dir2 = dir2->next;
    dir1->next = dir2->next;
    dir2->next = dir1;
    return (dir2);
}

int compare_time(struct stat *statbuf1, struct stat *statbuf2)
{
    time_t sec1 = statbuf1->st_mtime;
    time_t sec2 = statbuf2->st_mtime;

    if (sec1 < sec2)
        return (0);
    return (1);
}

dir_t *sort_dir_t_time(dir_t *dir)
{
    dir_t *use_dir = dir;
    struct stat *statbuf1 = malloc(sizeof(struct stat));
    struct stat *statbuf2 = malloc(sizeof(struct stat));

    for (int sorted = 0; sorted == 0;) {
        sorted = 1;
        use_dir = dir;
        while (use_dir->next != NULL) {
            stat(use_dir->t_name, statbuf1);
            stat(use_dir->next->t_name, statbuf2);
            if (compare_time(statbuf1, statbuf2) == 0) {
                sorted = 0;
                dir = exchange_place_dir(dir, use_dir);
            } else
                use_dir = use_dir->next;
        }
    }
    free(statbuf1);
    free(statbuf2);
    return (dir);
}

file_t *sort_file_t_time(file_t *dir)
{
    file_t *use_dir = dir;
    struct stat *statbuf1 = malloc(sizeof(struct stat));
    struct stat *statbuf2 = malloc(sizeof(struct stat));

    for (int sorted = 0; sorted == 0;) {
        sorted = 1;
        use_dir = dir;
        while (use_dir->next != NULL) {
            stat(use_dir->t_name, statbuf1);
            stat(use_dir->next->t_name, statbuf2);
            if (compare_time(statbuf1, statbuf2) == 0) {
                sorted = 0;
                dir = exchange_place(dir, use_dir);
            }
            else {
                use_dir = use_dir->next;
            }
        }
    }
    return (dir);
}
