/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

void ftp_noop(client_t * w, ftp_order_t * ftp_order)
{
    SEND_FTP(200, NULL);
}