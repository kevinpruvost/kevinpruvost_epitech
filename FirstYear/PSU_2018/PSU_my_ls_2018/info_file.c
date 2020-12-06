/*
** EPITECH PROJECT, 2019
** info_file.c
** File description:
** bootstrap funcs
*/

#include "my.h"

void print_rights(struct stat *statbuf)
{
    my_putstr((S_ISDIR(statbuf->st_mode)) ? "d" : "-");
    my_putstr((statbuf->st_mode & S_IRUSR) ? "r" : "-");
    my_putstr((statbuf->st_mode & S_IWUSR) ? "w" : "-");
    my_putstr((statbuf->st_mode & S_IXUSR) ? "x" : "-");
    my_putstr((statbuf->st_mode & S_IRGRP) ? "r" : "-");
    my_putstr((statbuf->st_mode & S_IWGRP) ? "w" : "-");
    my_putstr((statbuf->st_mode & S_IXGRP) ? "x" : "-");
    my_putstr((statbuf->st_mode & S_IROTH) ? "r" : "-");
    my_putstr((statbuf->st_mode & S_IWOTH) ? "w" : "-");
    my_putstr((statbuf->st_mode & S_IXOTH) ? "x" : "-");
    my_putstr(" ");
    my_put_nbr(statbuf->st_nlink);
    my_putstr(" ");
}

int print_owners(struct stat *statbuf, char *time, int size)
{
    struct passwd *pw = getpwuid(statbuf->st_uid);
    struct group *gr = getgrgid(statbuf->st_gid);

    my_putstr(gr->gr_name);
    my_putstr(" ");
    my_putstr(pw->pw_name);
    my_putstr(" ");
    for (int i = 0; i < size - my_strlen(my_getnbr(statbuf->st_size)); i++)
        my_putstr(" ");
    my_put_nbr(statbuf->st_size);
    my_putstr(" ");
    my_putstr(time);
    my_putstr(" ");
}
