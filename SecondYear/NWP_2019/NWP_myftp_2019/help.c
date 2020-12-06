/*
** EPITECH PROJECT, 2020
** help.c
** File description:
** help
*/

#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

char *load_file_in_mem(char const *filepath)
{
    struct stat *statbuff = malloc(sizeof(struct stat));
    int size = 0;
    char *buffer = 0;
    int fd;

    stat(filepath, statbuff);
    size = statbuff->st_size;
    buffer = malloc(sizeof(char) * (size + 1));
    fd = open(filepath, O_RDONLY);
    if (read(fd, buffer, size) == (-1))
        return (NULL);
    buffer[size] = 0;
    free(statbuff);
    close(fd);
    return (buffer);
}

void help_message(void)
{
    printf("%s\n", load_file_in_mem("./help_message"));
}

int help(int ac, char ** av)
{
    if (ac != 2)
        return EXIT_SUCCESS;
    if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0) {
        help_message();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}