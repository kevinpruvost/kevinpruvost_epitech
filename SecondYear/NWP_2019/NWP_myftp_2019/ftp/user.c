/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

static const user_t users[USER_NUMBER] = {{"ANONYMOUS", ""}};

void ftp_user(client_t * w, ftp_order_t * ftp_order)
{
    if (ftp_order->parameters == NULL || ftp_order->parameters[1] == NULL) {
        SEND_FTP_C(530, "Wrong USER command.");
        return;
    }
    if (w->login.user != NULL)
        free(w->login.user);
    w->login.user = strdup(ftp_order->parameters[1]);
    str_to_upper(w->login.user);
    SEND_FTP(331, NULL);
}

void ftp_pass(client_t * w, ftp_order_t * ftp_order)
{
    if (w->login.user == NULL) {
        SEND_FTP_C(503, "Login with USER first.");
        return;
    }
    w->login.passwd =
    (ftp_order->parameters != NULL && ftp_order->parameters[1] != NULL) ? \
strdup(ftp_order->parameters[1]) : strdup("");
    for (int i = 0; i < USER_NUMBER; ++i) {
        if (!strcmp(w->login.user, users[i].user) \
&& !strcmp(w->login.passwd, users[i].passwd)) {
            w->logged = true;
            SEND_FTP(230, NULL);
            return;
        }
    }
    SEND_FTP_C(530, "Login incorrect.");
    free(w->login.passwd);
    free(w->login.user);
    w->login.user = NULL;
    w->login.passwd = NULL;
}