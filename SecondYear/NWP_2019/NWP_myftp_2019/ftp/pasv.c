/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

static void print_pasv(client_t * w, struct sockaddr_in * sock_in)
{
    char msg[100];
    char buffer[BUFFER_SIZE] = {0};
    int j = strlen("Entering Passive Mode (");

    memset(msg, 0, 100);
    memset(buffer, 0, BUFFER_SIZE);
    strcpy(msg, "Entering Passive Mode (");
    for (int i = 0; w->ip_b[i] != 0; ++i) {
        msg[j++] = (w->ip_b[i] == '.') ? ',' : w->ip_b[i];
    }
    sprintf(buffer, "%s,%d,%d)", msg, w->pasv_port / 256,
    w->pasv_port - (w->pasv_port / 256 * 256));
    SEND_FTP_C(227, buffer);
}

static int init_port2(client_t * w, struct sockaddr_in * sock_in)
{
    socklen_t size = sizeof(sock_in);

    sock_in->sin_port = htons(0);
    sock_in->sin_family = AF_INET;
    sock_in->sin_addr.s_addr = INADDR_ANY;
    if (bind(w->fd_mod, (struct sockaddr *)sock_in, sizeof(*sock_in)) != 0)
        return EXIT_FAILURE;
    if (listen(w->fd_mod, CLIENT_NUMBER) != 0)
        return EXIT_FAILURE;
    if (getsockname(w->fd_mod, (struct sockaddr *)sock_in, &size) == -1)
        return EXIT_FAILURE;
    w->pasv_set = true;
    w->pasv_port = ntohs(sock_in->sin_port);
    print_pasv(w, sock_in);
    return EXIT_SUCCESS;
}

static int init_port(client_t * w, struct protoent * pr_e)
{
    struct sockaddr_in sock_in;
    int option = 1;

    (w->fd_mod != -1) ? close(w->fd_mod) : 0;
    pr_e = getprotobyname("TCP");
    if (pr_e == NULL)
        return EXIT_FAILURE;
    w->fd_mod = socket(AF_INET, SOCK_STREAM, pr_e->p_proto);
    if (w->fd_mod == -1)
        return EXIT_FAILURE;
    if (setsockopt(w->fd_mod, SOL_SOCKET, SO_REUSEADDR, \
(void *)(&option), sizeof(int)) < 0)
        fprintf(stderr, "setsockopt(SO_REUSEADDR) failed.\n");
    if (w->fd_mod < 0) {
        fprintf(stderr, "Error creating the TCP socket, exiting.\n");
        return EXIT_FAILURE;
    }
    bzero(&sock_in, sizeof(sock_in));
    return (init_port2(w, &sock_in));
}

void ftp_pasv(client_t * w, ftp_order_t * ftp_order)
{
    struct protoent * pr_e = NULL;

    if (init_port(w, pr_e) == EXIT_FAILURE) {
        SEND_FTP_C(500, "Illegal PASV.");
    }
}