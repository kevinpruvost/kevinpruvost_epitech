/*
** EPITECH PROJECT, 2019
** data2.c
** File description:
** continue data
*/

#include "my.h"

dir_t *init_dir(dir_t *dir, struct stat *statbuf, char *name)
{
    stat(name, statbuf);
    dir->t_name = name;
    dir->name = malloc(sizeof(char) * (my_strlen(name) + 1));
    for (int i = 0, j = my_strlen(name) - 1; j >= 0 && name[j] != '/'
    && name[j] != 0; i++, j--) {
        dir->name[i] = name[j];
        dir->name[i+1] = 0;
    }
    dir->name = my_revstr(dir->name);
    dir->time = correct_time(ctime(&statbuf->st_mtime));
    dir->next = NULL;
    dir->files = NULL;
    dir->sub = NULL;
    return (dir);
}

dir_t *process_dir(dir_t *dir, int mode, struct dirent *dp, DIR *pointer)
{
    for (int id = 0; dp != NULL;) {
        id = is_dir(format(dir->t_name, dp->d_name));
        if (dp->d_name[0] != '.' && dir->files == NULL && id == 0) {
            dir->files = create_file(format(dir->t_name, dp->d_name));
        } else if (dp->d_name[0] != '.' && dir->files != NULL && id == 0) {
            dir->files = add_file(dir->files, format(dir->t_name, dp->d_name));
        } if (dp->d_name[0] != '.' && dir->sub == NULL && id == 1) {
            dir->sub = create_dir(format(dir->t_name, dp->d_name), mode);
        } else if (dp->d_name[0] != '.' && dir->sub != NULL && id == 1) {
            dir->sub = add_dir(dir->sub, format(dir->t_name, dp->d_name), mode);
        }
        dp = readdir(pointer);
    }
    return (dir);
}
