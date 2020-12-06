/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "common.h"

bool stop_the_program(bool set)
{
    static bool stop = false;

    if (set) {
        stop = true;
    }
    return stop;
}

static int exit_here(char ** line)
{
    if (*line != NULL)
        free(*line);
    *line = NULL;
    return -1;
}

static void * first_malloc(char ** line, int total_red)
{
    if ((*line = malloc(total_red)) == NULL)
        return NULL;
    memset(*line, 0, total_red);
    return *line;
}

int my_getline(char ** line, int fd)
{
    char buffer[BUFFER_SIZE] = {0};
    int red = 0;
    int total_red = 0;

    while (!stop_the_program(false) && !ends_with(*line, "\n")) {
        memset(buffer, 0, BUFFER_SIZE);
        if ((red = read(fd, buffer, BUFFER_SIZE)) < 0)
            return exit_here(line);
        if (red == 0 && *line == NULL)
            return 0;
        total_red += red;
        if (*line == NULL && first_malloc(line, total_red + 1) == NULL)
            return -1;
        if ((*line = realloc(*line, total_red + 1)) == NULL)
            return exit_here(line);
        strcat(*line, buffer);
    }
    return total_red;
}