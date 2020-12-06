/*
** EPITECH PROJECT, 2020
** ftp.c
** File description:
** ftp
*/

#include "main.h"
#include <time.h>

static void fd_sets(network_t * w)
{
    int sd;
    client_t * node = w->client;
    FD_ZERO(&(w->readfds));

    FD_SET(w->local_fd, &(w->readfds));
    w->max_sd = w->local_fd;

    while (node != NULL) {
        sd = node->fd;

        if (sd > 0)
            FD_SET(sd, &(w->readfds));

        if (sd > w->max_sd)
            w->max_sd = sd;
        node = node->next;
    }
}

int ftp_loopy_loop(network_t * w, bool pass)
{
    static bool cond = true;
    int activity = 0;

    cond = (pass == false && cond == true) ? false : cond;
    if (!pass || !cond)
        return EXIT_FAILURE;
    fd_sets(w);
    activity = select(w->max_sd + 1, &(w->readfds), NULL, NULL, NULL);
    if (activity < 0) {
        fprintf(stderr, "Select error.\n");
        return EXIT_FAILURE;
    }
    if (FD_ISSET(w->local_fd, &(w->readfds))) {
        if (accept_new_client(w) == EXIT_FAILURE)
            return EXIT_FAILURE;
    } else {
        if (read_sockets(w) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int ftp_loop(network_t * w)
{
    bool cond = true;

    signal(SIGINT, signal_int_handler);
    signal(SIGUSR1, signal_usr1_handler);

    while (cond && errno != ENOENT) {
        if (ftp_loopy_loop(w, true) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}