/*
** EPITECH PROJECT, 2019
** dup_close_remake.c
** File description:
** dup close for mini_t
*/

#include "my.h"

int dup2m(mini_t *w, int fd)
{
    int error = -1;
    int error_dup = 0;
    int i = w->use_id;

    (fd == 1 && i != 0) ?
    (error_dup = dup2(w->fd[i-1][0], 0)) : (0);
    if (error_dup < 0)
        exit(84);
    (fd == 0 && i > 0) ? (i--) : (0);
    error_dup = dup2(w->fd[i][fd], fd);
    if (error_dup < 0)
        exit(84);
    return (error);
}

int closem(mini_t *w, int fd)
{
    int error = -1;
    static int i = 0;
    int passed = 0;

    i = w->use_id;
    for (; error != 0 && i < 50; i++) {
        error = close(w->fd[i][fd]);
        passed = 1;
    }
    (passed == 0) ? (i++) : (0);
    w->use_id = i;
    return (error);
}
