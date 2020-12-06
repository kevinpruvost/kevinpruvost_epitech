/*
** EPITECH PROJECT, 2019
** print_data.c
** File description:
** print datas
*/

#include "my.h"

int biggest_size(dir_t *dir)
{
    dir_t *use = dir;
    int size = 0;
    int test = 0;
    struct stat *statbuf = malloc(sizeof(struct stat));

    while (use->files != NULL) {
        stat(use->files->t_name, statbuf);
        test = my_strlen(my_getnbr(statbuf->st_size));
        use->files = use->files->next;
        if (size < test)
            size = test;
    }
    free(statbuf);
    return (size);
}

int print_dir_t(dir_t *dir, int l_o, int d_o)
{
    file_t *debut = dir->files;
    file_t *d_case = malloc(sizeof(dir_t));
    int size = biggest_size(dir);

    if (d_o == 1) {
        d_case->t_name = dir->t_name;
        d_case->time = dir->time;
        d_case->name = dir->name;
        (l_o == 1) ? (print_l_file(d_case, size)) : (my_putstr(d_case->name));
        my_putstr("\n");
        return (0);
    }
    my_putstr(dir->t_name);
    my_putstr(":\n");
    while (debut != NULL) {
        (l_o == 1) ? (print_l_file(debut, size)) : (my_putstr(debut->name));
        my_putstr("\n");
        debut = debut->next;
    }
}

int print_dir_t_no(dir_t *dir, int l_o, int d_o)
{
    file_t *debut = dir->files;
    file_t *d_case = malloc(sizeof(dir_t));
    int size = biggest_size(dir);

    if (d_o == 1) {
        d_case->t_name = dir->t_name;
        d_case->time = dir->time;
        d_case->name = dir->name;
        (l_o == 1) ? (print_l_file(d_case, size)) : (my_putstr(d_case->name));
        my_putstr("\n");
        return (0);
    }
    while (debut != NULL) {
        (l_o == 1) ? (print_l_file(debut, size)) : (my_putstr(debut->name));
        my_putstr("\n");
        debut = debut->next;
    }
}

void print_file_t(file_t *file, int l_o)
{
    file_t *debut = file;

    while (debut != NULL) {
        (l_o == 1) ? (print_l_file(debut, 9)) : (my_putstr(debut->name));
        my_putstr("\n");
        debut = debut->next;
    }
}
