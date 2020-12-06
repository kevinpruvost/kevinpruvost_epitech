/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

bool dir_permissions(const char * path)
{
    if (access(path, R_OK) == 0) {
        return true;
    } else
        return false;
}

static char * dirup(char * dir)
{
    char * new_dir = NULL;

    if (dir == NULL)
        return NULL;
    new_dir = strdup(dir);
    if (new_dir[strlen(new_dir) - 1] == '/')
        new_dir[strlen(new_dir) - 1] = 0;
    while (new_dir[0] != 0 && new_dir[strlen(new_dir) - 1] != '/')
        new_dir[strlen(new_dir) - 1] = 0;
    if (strlen(new_dir) != 1 && new_dir[strlen(new_dir - 1)] == '/')
        new_dir[strlen(new_dir) - 1] = 0;
    return new_dir;
}

void ftp_cdup(client_t * w, ftp_order_t * ftp_order)
{
    char * dir = dirup(w->path);

    if (dir == NULL || dir[0] == 0) {
        SEND_FTP(550, NULL);
        return;
    }
    if (!dir_exists(dirup(w->path))) {
        SEND_FTP(550, NULL);
    } else {
        free(w->path);
        w->path = strdup(dir);
        SEND_FTP(250, NULL);
    }
    free(dir);
}