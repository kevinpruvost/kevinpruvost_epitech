/*
** EPITECH PROJECT, 2018
** load_array.c
** File description:
** Functions to load the array.
*/

#include "include/my.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

char *load_file_in_mem1(char const *filepath)
{
    struct stat *statbuff = malloc(sizeof(struct stat));
    int size = 0;
    char *buffer = 0;
    int fd;

    stat(filepath, statbuff);
    size = statbuff->st_size;
    buffer = malloc(size);
    fd = open(filepath, O_RDONLY);
    if (read(fd, buffer, size) == (-1))
        exit(84);
    for (int i = size; buffer[i+1] != 0; i++)
        buffer[i] = 0;
    free(statbuff);
    close(fd);
    return (buffer);
}

void forload(char *content, int *lengthmax, int *lines)
{
    int length = 0;

    for (int i = 0; content[i] != 0; i++) {
        if (content[i] == '\n' && content[i+1] != 0) {
            *lines += 1;
            length = 0;
        } else
            length++;
        if (length > *lengthmax) {
            *lengthmax = length;
        }
    }
}

char **load_2d_arr_from_file(char const *filepath)
{
    char *content = load_file_in_mem1(filepath);
    char **array = 0;
    int lines = 0;
    int lengthmax = 0;
    int a = 0;

    forload(content, &lengthmax, &lines);
    array = malloc(sizeof(char *) * (lines + 1));
    for (a++; content[a-1] != '\n'; a++);
    for (int i = 0; i < lines; i++, a++) {
        array[i] = malloc(sizeof(char) * (lengthmax + 1));
        for (int j = 0; content[a] != '\n' && content[a] != 0; j++, a++) {
            array[i][j] = content[a];
        }
    }
    array[lines] = malloc(sizeof(char));
    array[lines][0] = 0;
    free(content);
    return (array);
}

void free_2d_array(char **array, int nb_rows)
{
    int i = 0;

    for (i = 0; i < nb_rows; i++);
    for (; i >= 0; i--) {
        free(array[i]);
    }
    free(array);
}
