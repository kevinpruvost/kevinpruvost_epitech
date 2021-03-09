/*
** EPITECH PROJECT, 2018
** load_file_in_mem.c
** File description:
** bstrap
*/

#include "../include/my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

char *load_file_in_mem(char *filepath)
{
    struct stat *statbuff = malloc(sizeof(struct stat));
    int size = 0;
    char *buffer = 0;
    int fd;

    if ((stat(filepath, statbuff)) == -1) {
        my_putstr_fd(filepath, 2);
        my_putstr_fd(": No such file or directory.\n", 2);
    }
    size = statbuff->st_size;
    if (size >= 65536)
        return (NULL);
    buffer = malloc(sizeof(char) * (size + 1));
    fd = open(filepath, O_RDONLY);
    if (read(fd, buffer, size) == (-1))
        return (NULL);
    buffer[size] = 0;
    free(statbuff);
    close(fd);
    return (buffer);
}
