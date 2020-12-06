/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"
#include <sys/ioctl.h>

int more_pipe(int mode)
{
    static char * my_fifo = "./fifo";
    static bool done = false;
    static int fd = 0;
    static bool closed = false;

    if (closed || !done) {
        mkfifo(my_fifo, 0777);
        fd = open(my_fifo, O_RDWR);
        done = true;
        closed = false;
    }
    if (mode == 3) {
        close(fd);
        closed = true;
        remove(my_fifo);
    }
    return fd;
}

int create_fd_set_form_clients(int distant_fd, fd_set * fd_set)
{
    int fd_p = more_pipe(1);
    int fd_max = (fd_p > distant_fd) ? fd_p : distant_fd;

    FD_ZERO(fd_set);
    FD_SET(distant_fd, fd_set);
    FD_SET(STDIN_FD, fd_set);
    FD_SET(fd_p, fd_set);
    return (fd_max);
}

void client_loop(int distant_fd)
{
    account_t account = {NULL, {0}, distant_fd};

    read_server(distant_fd, &account);
    while (!stop_the_program(false)) {
        printf("[CLIENT] > ");
        fflush(stdout);
        if (read_server_and_client(distant_fd, &account) == EXIT_FAILURE)
            break;
    }
    (account.username != NULL) ? free(account.username) : 0;
}

client_socket_t create_socket(const char * ip, uint16_t port)
{
    client_socket_t w;
    w.distant_fd = 0;
    w.error = true;

    w.distant_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (w.distant_fd < 0)
        return w;
    bzero(&(w.distant_sock), sizeof(w.distant_sock));
    w.distant_sock.sin_family = AF_INET;
    if (inet_aton(ip, (struct in_addr *)&(w.distant_sock.sin_addr.s_addr)) == 0)
        return w;
    w.distant_sock.sin_port = htons(port);
    if (connect(w.distant_fd, (struct sockaddr *)&(w.distant_sock), \
sizeof(w.distant_sock)) != 0)
        return w;
    w.error = false;
    return w;
}

void close_socket(client_socket_t * w)
{
    close(w->distant_fd);
    more_pipe(3);
}