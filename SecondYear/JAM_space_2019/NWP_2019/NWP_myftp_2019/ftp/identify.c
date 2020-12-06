/*
** EPITECH PROJECT, 2020
** identify.c
** File description:
** con de toi
*/

#include "main.h"

const void (* funcs[])(client_t *, ftp_order_t *) = {\
ftp_user, \
ftp_pass, \
ftp_cwd, \
ftp_cdup, \
ftp_quit, \
ftp_dele, \
ftp_pwd, \
ftp_pasv, \
ftp_port, \
ftp_help, \
ftp_noop, \
ftp_retr, \
ftp_stor, \
ftp_list\
};

void launch_command(client_t * w, ftp_order_t * ftp)
{
    if (w->logged == true || ftp->order == USER || ftp->order == PASS) {
        if (ftp->order == ERROR || ftp->order == NO_ORDER)
            SEND_FTP(500, NULL);
        else
            funcs[ftp->order](w, ftp);
    } else {
        SEND_FTP_C(530, "Please login with USER and PASS.");
    }
}

static void identify_order(ftp_order_t * ftp_order, char * line)
{
    static char * compares[] = {"USER ", "PASS ", "PASS", "CWD ", "CDUP", \
"QUIT", "DELE ", "PWD", "PASV", "PORT ", "HELP ", "HELP", "NOOP", \
"RETR ", "STOR ", "LIST ", "LIST", NULL};
    static int ints[] = {USER, PASS, PASS, CWD, CDUP, QUIT, DELE, PWD, PASV, \
PORT, HELP, HELP, NOOP, RETR, STOR, LIST, LIST, -1};
    char * cline = strdup(line);

    str_to_upper(cline);
    for (int i = 0; compares[i] != NULL; ++i) {
        if (starts_with(cline, compares[i])) {
            ftp_order->order = ints[i];
            line = line + strlen(compares[i]);
            free(cline);
            return;
        }
    }
    free(cline);
    ftp_order->order = ERROR;
}

static void identify_ftp_parameters(ftp_order_t * ftp_order, char * line)
{
    if (ftp_order->parameters != NULL)
        free_2darray((void **)ftp_order->parameters);
    ftp_order->parameters = split(line, " ");
}

void identify_ftp_command(ftp_order_t * ftp_order, char * line)
{
    identify_order(ftp_order, line);
    if (ftp_order->order == ERROR || !ends_with(line, CRLF)) {
        ftp_order->order = ERROR;
        print_raw_str(line);
        return;
    }
    line[strlen(line) - 2] = 0;
    identify_ftp_parameters(ftp_order, line);
}