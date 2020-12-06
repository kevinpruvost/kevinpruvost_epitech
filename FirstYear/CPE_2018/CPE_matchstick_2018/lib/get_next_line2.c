/*
** EPITECH PROJECT, 2019
** get_next_line.c
** File description:
** gnl with getline
*/

#include "my.h"

char *get_next_line(int fd)
{
    char *buf = malloc(sizeof(char) * 255);
    size_t size = 255;

    getline(&buf, &size, stdin);
    for (int i = 0; buf[i] != 0; i++)
        if (buf[i] == '\n')
            buf[i] = 0;
    return (buf);
}
