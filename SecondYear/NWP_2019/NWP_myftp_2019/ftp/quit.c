/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

void ftp_quit(client_t * w, ftp_order_t * ftp_order)
{
    SEND_FTP(221, NULL);
    w->logged = false;
    free(w->login.user);
    w->login.user = NULL;
    free(w->login.passwd);
    w->login.passwd = NULL;
}