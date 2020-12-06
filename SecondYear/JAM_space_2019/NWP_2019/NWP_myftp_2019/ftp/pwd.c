/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

void ftp_pwd(client_t * w, ftp_order_t * ftp_order)
{
    if (w->path == NULL) {
        SEND_FTP(550, NULL);
        return;
    }
    SEND_FTP(257, w->path);
}