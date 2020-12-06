/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

static bool valid_tab(char ** tab)
{
    int size = 0;

    if (tab == NULL)
        return false;
    for (; tab[size] != NULL; ++size) {
        if (!is_numeric(tab[size]))
            return false;
    }
    if (size != 6)
        return false;
    return true;
}

static char * get_ip(char ** tab)
{
    char * ip = malloc(sizeof(char) * 16);
    int x = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; tab[i][j] != 0; ++j) {
            ip[x++] = tab[i][j];
        }
        ip[x++] = (i != 3) ? '.' : 0;
    }
    return ip;
}

static int init_port2(client_t * w, char ** tab, struct sockaddr_in * sock_in)
{
    char *ip = get_ip(tab);
    uint16_t port = atoi(tab[4]) * 256 + atoi(tab[5]);

    free_2darray((void **)tab);
    w->port_port = port;
    if (w->ip != NULL)
        free(w->ip);
    w->ip = ip;
    w->port_set = true;
    w->port_port = port;
    SEND_FTP_C(200, "PORT command success.");
    return EXIT_SUCCESS;
}

static int init_port(client_t * w, char ** tab, struct protoent * pr_e)
{
    struct sockaddr_in sock_in;

    (w->fd_mod != -1) ? close(w->fd_mod) : 0;
    return (init_port2(w, tab, &sock_in));
}

void ftp_port(client_t * w, ftp_order_t * ftp_order)
{
    char **tab = NULL;
    struct protoent * pr_e = NULL;

    if (ftp_order->parameters == NULL || ftp_order->parameters[1] == NULL) {
        SEND_FTP_C(550, "PORT command format unrecognized.");
        return;
    }
    tab = split(ftp_order->parameters[1], ",");
    for (int i = 0; tab[i] != NULL; ++i) {
        if (tab[i][strlen(tab[i]) - 1] == ',')
            tab[i][strlen(tab[i]) - 1] = 0;
    }
    if (!tab || !valid_tab(tab))
        SEND_FTP_C(500, "Illegal PORT command.");
    else {
        if (init_port(w, tab, pr_e) == EXIT_FAILURE)
            SEND_FTP_C(500, "Illegal PORT command.");
    }
}