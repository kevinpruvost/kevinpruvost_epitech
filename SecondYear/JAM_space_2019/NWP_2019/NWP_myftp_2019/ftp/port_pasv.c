/*
** EPITECH PROJECT, 2020
** port_pasv.c
** File description:
** port pasv
*/

#include "main.h"

static int port_way(client_t * w, struct sockaddr_in * s_in, socklen_t sizes)
{
    int option = 1;

    w->fd_mod = socket(PF_INET, SOCK_STREAM, 0);
    if (w->fd_mod == -1)
        return -1;
    if (setsockopt(w->fd_mod, IPPROTO_TCP, TCP_NODELAY, \
(void *)(&option), sizeof(int)) < 0)
        fprintf(stderr, "setsockopt(TCP_NODELAY) failed.\n");
    if (w->fd_mod < 0) {
        fprintf(stderr, "Error creating the TCP socket, exiting.\n");
        return -1;
    }
    bzero(s_in, sizeof(struct sockaddr_in));
    s_in->sin_addr.s_addr = inet_addr(w->ip);
    s_in->sin_family = AF_INET;
    s_in->sin_port = htons(w->port_port);
    if (connect(w->fd_mod, (struct sockaddr *)s_in, sizeof(*(s_in))) < 0)
        return -1;
    return w->fd_mod;
}

static int fd_select(client_t * w, struct sockaddr_in * s_in, socklen_t sizes)
{
    int fd = w->fd_mod;
    int activity = 0;
    fd_set read_fds;

    FD_ZERO(&read_fds);
    FD_SET(w->fd_mod, &read_fds);

    activity = select(w->fd_mod + 1, &read_fds, NULL, NULL, NULL);
    if (activity == -1)
        return -1;
    if (FD_ISSET(w->fd_mod, &read_fds)) {
        fd = accept(w->fd_mod, (struct sockaddr *)s_in, &sizes);
    }
    return fd;
}

int open_pasv_port(client_t * w)
{
    struct sockaddr_in s_in;
    socklen_t sizes = sizeof(s_in);
    int fd = 0;

    signal(SIGINT, signal_handler);
    signal(SIGUSR1, signal_handler2);
    ftp_loopy_loop(NULL, false);
    if (w->port_set) {
        fd = port_way(w, &s_in, sizes);
    } else
        fd = fd_select(w, &s_in, sizes);
    return fd;
}

void close_pasv_port(client_t * client)
{
    close(client->fd_mod);
    client->pasv_set = false;
    client->port_set = false;
    client->port_port = -1;
    client->pasv_port = -1;
    if (client->ip != NULL) {
        free(client->ip);
        client->ip = NULL;
    }
}