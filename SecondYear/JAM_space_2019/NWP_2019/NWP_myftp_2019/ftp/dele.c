/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

char * assemble_path_file(client_t * w, ftp_order_t * ftp_order)
{
    size_t size = 2 + strlen(w->path) + strlen(ftp_order->parameters[1]);
    char * filename = malloc(sizeof(char) * size);

    memset(filename, 0, size);
    strcpy(filename, w->path);
    filename[strlen(filename)] = '/';
    strcat(filename, ftp_order->parameters[1]);
    return filename;
}

void ftp_dele(client_t * w, ftp_order_t * ftp_order)
{
    char * file_name = NULL;

    if (ftp_order->parameters == NULL || ftp_order->parameters[1] == NULL) {
        SEND_FTP_C(550, "DELE command format unrecognized.");
        return;
    }
    file_name = assemble_path_file(w, ftp_order);
    if (access(file_name, R_OK) != 0) {
        SEND_FTP_C(550, "Permission denied.");
        return;
    }
    if (remove(file_name) == 0) {
        SEND_FTP_C(250, "File deleted.");
    } else {
        SEND_FTP_C(550, "File not found.");
    }
    free(file_name);
}