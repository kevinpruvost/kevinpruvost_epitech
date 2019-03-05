/*
** EPITECH PROJECT, 2019
** reverse.c
** File description:
** reverse
*/

#include "my.h"

void reverse_print_dir_t_no(dir_t *dir, int l_o)
{
    file_t *last_print;
    file_t *use = dir->files;
    int n_print = 1;
    int size = 9;

    while (use->next != NULL) {
        n_print++;
        use = use->next;
    }
    for (int i = 0; i < n_print; i++) {
        last_print = use;
        (l_o == 1) ? (print_l_file(use, size)) : (my_putstr(use->name));
        my_putstr("\n");
        use = dir->files;
        if (use == last_print)
            break;
        while (use->next != last_print)
            use = use->next;
    }
}

void reverse_print_dir_t(dir_t *dir, int l_o)
{
    file_t *last_print;
    file_t *use = dir->files;
    int n_print = 1;

    my_putstr(dir->t_name);
    my_putstr(":\n");
    while (use->next != NULL) {
        n_print++;
        use = use->next;
    }
    for (int i = 0; i < n_print; i++) {
        last_print = use;
        (l_o == 1) ? (print_l_file(use, 9)) : (my_putstr(use->name));
        my_putstr("\n");
        use = dir->files;
        if (use == last_print)
            break;
        while (use->next != last_print)
            use = use->next;
    }
}
