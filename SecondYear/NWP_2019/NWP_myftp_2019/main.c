/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** main
*/

#include "main.h"

int get_parameters(network_t * w, char ** av)
{
    if (!is_numeric(av[1])) {
        fprintf(stderr, "Port parameter is not right.\n");
        help_message();
        return EXIT_FAILURE;
    }
    w->port = (uint16_t)atoi(av[1]);
    w->path = av[2];
    if (!dir_exists(w->path)) {
        fprintf(stderr, "'%s' path parameter cannot be opened.\n", w->path);
        return EXIT_FAILURE;
    }
    if (chdir(w->path) == -1) {
        fprintf(stderr, "Error: Chdir cannot open path\n");
        return EXIT_FAILURE;
    }
    w->client = NULL;
    return EXIT_SUCCESS;
}

void destroy_network(network_t * w)
{
    client_t * node = w->client;

    while (node != NULL) {
        w->client = w->client->next;
        free(node->path);
        (node->login.user != NULL) ? free(node->login.user) : 0;
        (node->login.passwd != NULL) ? free(node->login.passwd) : 0;
        free(node);
        node = w->client;
    }
    MY_FORK_DELETE_ALL();
}

int main(int ac, char ** av)
{
    network_t w;

    if (help(ac, av) == EXIT_FAILURE)
        return EXIT_SUCCESS;

    if (ac != 3 || !av[1] || !av[2]) {
        fprintf(stderr, "Invalid arguments, exiting.\n");
        help_message();
        return EXIT_FAILURE;
    }

    if (get_parameters(&w, av) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (network(&w) == EXIT_FAILURE) {
        destroy_network(&w);
        return EXIT_FAILURE;
    }
    destroy_network(&w);
    return EXIT_SUCCESS;
}