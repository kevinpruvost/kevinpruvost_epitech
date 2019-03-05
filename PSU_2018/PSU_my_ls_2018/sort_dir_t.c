/*
** EPITECH PROJECT, 2019
** sort_dir_t.c
** File description:
** sort dir
*/

#include "my.h"

int compare_str(char *s1, char *s2)
{
    int ok = 1;

    if (s1 == NULL || s2 == NULL)
        return (1);
    for (int i = 0; s1[i] != 0 && s2[i] != 0; i++) {
        if (s1[i] >= 65 && s1[i] <= 90 && s2[i] >= 97 && s2[i] <= 122)
            if (s1[i] + 32 > s2[i])
                return (0);
        if (s2[i] >= 65 && s2[i] <= 90 && s1[i] >= 97 && s1[i] <= 122)
            if (s2[i] + 32 >= s1[i])
                return (1);
        if (s1[i] < s2[i])
            return (1);
        if (s1[i] > s2[i])
            return (0);
    }
    if (my_strlen(s1) > my_strlen(s2))
        return (0);
    return (1);
}

dir_t *exchange_place_dir(dir_t *init, dir_t *dir)
{
    dir_t *dir1 = init;
    dir_t *dir2 = dir;
    dir_t *dir3 = dir->next;

    if (dir1 == dir2) {
        dir2 = comp_exchange_dir(dir1, dir2);
        return (dir2);
    }
    while (dir1->next != dir2)
        dir1 = dir1->next;
    if (dir3 != NULL) {
        dir2->next = dir3->next;
        dir3->next = dir2;
        dir1->next = dir3;
    } else {
        dir2->next = dir1;
        dir1->next = NULL;
        return (dir2);
    }
    return (init);
}

file_t *exchange_place(file_t *init, file_t *dir)
{
    file_t *dir1 = init;
    file_t *dir2 = dir;
    file_t *dir3 = dir->next;

    if (dir1 == dir2) {
        dir2 = comp_exchange_file(dir1, dir2);
        return (dir2);
    }
    while (dir1->next != dir2)
        dir1 = dir1->next;
    if (dir3 != NULL) {
        dir2->next = dir3->next;
        dir3->next = dir2;
        dir1->next = dir3;
    } else {
        dir2->next = dir1;
        dir1->next = NULL;
        return (dir2);
    }
    return (init);
}

dir_t *sort_dir_t(dir_t *dir, int mode)
{
    dir_t *use_dir = dir;

    if (dir == NULL)
        return (NULL);
    for (int sorted = 0; sorted == 0;) {
        sorted = 1;
        use_dir = dir;
        while (use_dir->next != NULL) {
            if (compare_str(use_dir->name, use_dir->next->name) == 0) {
                sorted = 0;
                dir = exchange_place_dir(dir, use_dir);
            } else
                use_dir = use_dir->next;
        }
    }
    if (mode == 1)
        dir = sort_dir_t_time(dir);
    return (dir);
}

file_t *sort_file_t(file_t *dir, int mode)
{
    file_t *use_dir = dir;

    if (dir == NULL)
        return (NULL);
    for (int sorted = 0; sorted == 0;) {
        sorted = 1;
        use_dir = dir;
        while (use_dir->next != NULL) {
            if (compare_str(use_dir->name, use_dir->next->name) == 0) {
                sorted = 0;
                dir = exchange_place(dir, use_dir);
            } else
                use_dir = use_dir->next;
        }
    }
    if (mode == 1)
        dir = sort_file_t_time(dir);
    return (dir);
}
