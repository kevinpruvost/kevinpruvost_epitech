/*
** EPITECH PROJECT, 2019
** launch_command.c
** File description:
** launch command
*/

#include "my.h"

int launch_command(char *cmd, ai_t *w)
{
    char *line;
    int err;

    my_putstr(cmd);
    line = get_next_line(0);
    err = detect_end(line, w);
    return (err);
}
