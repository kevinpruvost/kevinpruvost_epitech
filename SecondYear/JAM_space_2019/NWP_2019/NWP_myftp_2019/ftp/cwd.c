/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

char * create_possible_path(char * base, char * new)
{
    char * path = malloc(sizeof(char) * (strlen(base) + strlen(new) + 2));
    char * resolved = NULL;

    for (int i = 0; i < strlen(base) + strlen(new) + 1; ++i) {
        path[i] = (i < strlen(base)) ? base[i] : path[i];
        path[i] = (i == strlen(base)) ? '/' : path[i];
        path[i] = (i > strlen(base)) ? new[i - strlen(base) - 1] : path[i];
    }
    path[strlen(base) + strlen(new) + 1] = 0;
    resolved = realpath(path, resolved);
    free(path);
    return resolved;
}

void ftp_cwd(client_t * w, ftp_order_t * ftp_order)
{
    char * possible_path = NULL;

    if (ftp_order->parameters == NULL || ftp_order->parameters[1] == NULL) {
        SEND_FTP(550, NULL);
        return;
    }
    possible_path = create_possible_path(w->path, ftp_order->parameters[1]);
    if (!dir_exists(possible_path)) {
        SEND_FTP_C(550, "Failed to change directory.");
    } else {
        free(w->path);
        w->path = possible_path;
        SEND_FTP(250, NULL);
    }
}