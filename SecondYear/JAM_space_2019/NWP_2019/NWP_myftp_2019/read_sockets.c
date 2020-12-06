/*
** EPITECH PROJECT, 2020
** read_sockets.c
** File description:
** read_sockets
*/

#include "main.h"

int read_sfor_line(ftp_order_t * ftp_order, char * line, client_t * node)
{
    char ** commands = split(line, "\r\n");

    if (commands == NULL)
        return EXIT_FAILURE;
    for (int i = 0; commands[i] != NULL; ++i) {
        if (!strcmp(commands[i], "\r\n")) {
            continue;
        }
        identify_ftp_command(ftp_order, commands[i]);
        (ftp_order->order == QUIT) ? my_send(node->fd, 221, NULL) : 0;
        (ftp_order->order == ERROR) ? my_send_custom(node->fd, \
(node->logged) ? 500 : 530, "Permission denied.") : 0;
        if (ftp_order->order != NO_ORDER && ftp_order->order != QUIT \
&& ftp_order->order != ERROR)
            launch_command(node, ftp_order);
    }
    free_2darray((void **)commands);
    return (ftp_order->order == QUIT) ? 5 : EXIT_SUCCESS;
}

void rewrite_additional_lines(char * line)
{
    int i = 0;

    while (line[i] == '\r' && line[i+1] == '\n'
    && line[i+2] == '\r' && line[i+3] == '\n') {
        remove_first_chars(line, 2);
    }
}

int read_build_line(char * line, client_t * node)
{
    int readret = 0;
    char buffer[BUFFER_SIZE];

    memset(buffer, 0, BUFFER_SIZE);
    for (readret = read(node->fd, buffer, BUFFER_SIZE); readret > 0 && \
!ends_with(buffer, CRLF); readret = read(node->fd, buffer, BUFFER_SIZE)) {
        if (readret <= 0)
            return 0;
        (line[0] == 0) ? strcpy(line, buffer) : strcat(line, buffer);
        memset(buffer, 0, BUFFER_SIZE);
    }
    if (readret <= 0)
        return readret;
    (line[0] == 0) ? strcpy(line, buffer) : strcat(line, buffer);
    rewrite_additional_lines(line);
    return readret;
}

int read_sfor(network_t * w, ftp_order_t * ftp, char * line, client_t * node)
{
    int readret = 1;

    if (!FD_ISSET(node->fd, &(w->readfds)))
        return EXIT_SUCCESS;
    readret = read_build_line(line, node);
    if (readret > 0) {
        if (read_sfor_line(ftp, line, node) == 5)
            return 5;
    } else if (readret == 0)
        return 5;
    return EXIT_SUCCESS;
}

int read_sockets(network_t * w)
{
    ftp_order_t ftp = {NO_ORDER, NULL};
    char line[BUFFER_SIZE] = {0};
    int ret = 0;
    client_t * to_remove = NULL;

    memset(line, 0, BUFFER_SIZE);
    usleep(50000);
    for (client_t * node = w->client; node != NULL;) {
        if ((ret = read_sfor(w, &ftp, line, node)) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        } else if (ret == 5) {
            close(node->fd);
            to_remove = node;
            node = node->next;
            remove_client(w, to_remove);
        } else
            node = node->next;
    }
    (ftp.parameters != NULL) ? free_2darray((void **)ftp.parameters) : 0;
    return EXIT_SUCCESS;
}