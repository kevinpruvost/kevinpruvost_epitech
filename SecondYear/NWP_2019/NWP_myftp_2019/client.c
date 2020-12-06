/*
** EPITECH PROJECT, 2020
** client.c
** File description:
** client
*/

#include "main.h"

client_t * new_client(char * path, int fd, struct sockaddr_in socket, char * ip)
{
    client_t * client = malloc(sizeof(client_t));

    client->path = malloc(sizeof(char) * (strlen(path) + 1));
    strcpy(client->path, path);
    client->fd = fd;
    client->socket = socket;
    client->next = NULL;
    client->login.user = NULL;
    client->login.passwd = NULL;
    client->logged = false;
    client->port_port = 0;
    client->pasv_port = 0;
    client->pasv_set = false;
    client->port_set = false;
    client->fd_mod = -1;
    client->ip_b = ip;
    client->ip = NULL;
    return client;
}

void add_client(network_t * w, client_t * new)
{
    client_t * node = w->client;

    if (node == NULL) {
        w->client = new;
        return;
    }
    while (node->next != NULL)
        node = node->next;
    node->next = new;
}

static void destroy_client(client_t * client)
{
    close(client->fd);
    free(client->path);
    if (client->fd_mod != -1)
        close(client->fd_mod);
    (client->login.user != NULL) ? free(client->login.user) : 0;
    if (client->login.passwd != NULL)
        free(client->login.passwd);
    if (client->ip != NULL)
        free(client->ip);
    MY_FORK_DELETE_CLIENT(client);
    free(client);
}

void remove_client(network_t * w, client_t * client)
{
    client_t * node = w->client;

    BLOCK_SIGNALS;
    if (node == client) {
        w->client = node->next;
        destroy_client(node);
        return;
    }
    while (node != NULL && node->next != NULL && node->next != client) {
        node = node->next;
    }
    if (node->next == client) {
        node->next = client->next;
        destroy_client(node);
    }
}

int accept_new_client(network_t * w)
{
    w->distant_fd = accept(w->local_fd, (struct sockaddr *)&w->distant_sock, \
(socklen_t *)&w->addr_len);
    if (w->distant_fd < 0) {
        fprintf(stderr, "Local accept failed, exiting.\n");
        return EXIT_FAILURE;
    }
    my_send_custom(w->distant_fd, 220, "Le joli FTP.");
    add_client(w, new_client(w->path, w->distant_fd, w->distant_sock, w->ip));
    return EXIT_SUCCESS;
}