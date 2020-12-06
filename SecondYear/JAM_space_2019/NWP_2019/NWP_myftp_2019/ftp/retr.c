/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

void download_file(FILE * file, int fd_new, client_t * w)
{
    char str[BUFFER_SIZE];

    memset(str, 0, BUFFER_SIZE);
    SEND_FTP_C(150, "Opening BINARY mode data connection.");
    while (fgets(str, BUFFER_SIZE - 1, file)) {
        write(fd_new, str, strlen(str));
        memset(str, 0, BUFFER_SIZE);
    }
    fclose(file);
    SEND_FTP_C(226, "Transfer complete.");
    (fd_new != -1) ? close(fd_new) : 0;
    ftp_loopy_loop(NULL, false);
}

static void retr(client_t * w, ftp_order_t * ftp_order)
{
    int fd_new = -1;
    char * filename = assemble_path_file(w, ftp_order);
    FILE * file = NULL;

    if (access(filename, R_OK) != 0) {
        SEND_FTP_C(550, "Permission denied.");
        free(filename);
        return;
    }
    file = fopen(filename, "r+");
    fd_new = open_pasv_port(w);
    if (file == NULL) {
        SEND_FTP_C(550, "Failed to open file.");
        (fd_new != -1) ? close(fd_new) : 0;
    } else if (fd_new == -1) {
        SEND_FTP_C(425, "Problem with connection.");
        (file != NULL) ? fclose(file) : 0;
    } else
        download_file(file, fd_new, w);
    free(filename);
}

void ftp_retr(client_t * w, ftp_order_t * ftp_order)
{
    int pid = 0;

    if (!w->pasv_set && !w->port_set) {
        SEND_FTP(425, NULL);
        return;
    }
    if (ftp_order->parameters == NULL || ftp_order->parameters[1] == NULL) {
        SEND_FTP_C(550, "RETR command format unrecognized.");
        return;
    }
    UNBLOCK_SIGNALS;
    if ((pid = MY_FORK(w)) == -1) {
        SEND_FTP_C(425, "Fork problem.");
        return;
    }
    if (pid == 0)
        retr(w, ftp_order);
    close_pasv_port(w);
}