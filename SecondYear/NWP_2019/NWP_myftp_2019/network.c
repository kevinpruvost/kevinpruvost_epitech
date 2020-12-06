/*
** EPITECH PROJECT, 2020
** network.c
** File description:
** network
*/

#include "main.h"

static int port_part(network_t * w)
{
    w->local_sock.sin_family = AF_INET;
    if (inet_aton(IP, (struct in_addr *)&w->local_sock.sin_addr.s_addr) == 0) {
        fprintf(stderr, "Invalid IP, exiting.\n");
        return EXIT_FAILURE;
    }
    w->ip = inet_ntoa(w->local_sock.sin_addr);
    w->local_sock.sin_port = htons(w->port);
    if (bind(w->local_fd, (struct sockaddr *)&w->local_sock, \
sizeof(w->local_sock)) != 0) {
        fprintf(stderr, "Bind failed with port %u, exiting.\n", w->port);
        return EXIT_FAILURE;
    }
    if (listen(w->local_fd, CLIENT_NUMBER) != 0) {
        fprintf(stderr, "Listen failed, exiting\n");
        return EXIT_FAILURE;
    }
    w->addr_len = sizeof(w->distant_sock);
    return EXIT_SUCCESS;
}

int network(network_t * w)
{
    int option = 1;

    w->pr_e = getprotobyname("TCP");
    w->local_fd = socket(AF_INET, SOCK_STREAM, w->pr_e->p_proto);
    if (setsockopt(w->local_fd, SOL_SOCKET, SO_REUSEADDR,
        (void *)(&option), sizeof(int)) < 0)
        fprintf(stderr, "setsockopt(SO_REUSEADDR) failed.\n");
    if (w->local_fd < 0) {
        fprintf(stderr, "Error creating the TCP socket, exiting.\n");
        return EXIT_FAILURE;
    }
    bzero(&w->local_sock, sizeof(w->local_sock));
    if (port_part(w) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (ftp_loop(w) == EXIT_FAILURE) {
        close(w->local_fd);
        return EXIT_FAILURE;
    }
    close(w->local_fd);
    return EXIT_SUCCESS;
}