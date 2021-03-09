/*
** EPITECH PROJECT, 2019
** prepare_pipe.c
** File description:
** prepare pipe funcs
*/

#include "my.h"

int pipe_read(mini_t *w)
{
    close(w->fd[0][1]);
    return (dup2(w->fd[0][0], 0));
}

int pipe_write(mini_t *w)
{
    return (dup2(w->fd[0][1], 1));
}
