/*
** EPITECH PROJECT, 2020
** pass.c
** File description:
** pass
*/

#include "main.h"

void upload_file(int file, int fd_new, client_t * w)
{
    char str[BUFFER_SIZE];

    memset(str, 0, BUFFER_SIZE);
    SEND_FTP_C(150, "Opening BINARY mode data connection.");
    for (int ret = read(fd_new, str, BUFFER_SIZE - 1); ret > 0;) {
        write(file, str, strlen(str));
        memset(str, 0, BUFFER_SIZE);
        ret = read(fd_new, str, BUFFER_SIZE - 1);
    }
    close(file);
    SEND_FTP_C(226, "Transfer complete.");
    (fd_new != -1) ? close(fd_new) : 0;
    ftp_loopy_loop(NULL, false);
}

static void stor(client_t * w, ftp_order_t * ftp_order)
{
    int fd_new = -1;
    char * filename = assemble_path_file(w, ftp_order);
    int file = -1;

    file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    fd_new = open_pasv_port(w);
    if (fd_new == -1 || file == -1) {
        SEND_FTP_C(425, \
((file == -1) ? "Cannot open file." : "Problem with connection."));
        (fd_new != -1) ? close(fd_new) : 0;
        (file != -1) ? close(file) : 0;
    } else
        upload_file(file, fd_new, w);
    free(filename);
}

void ftp_stor(client_t * w, ftp_order_t * ftp_order)
{
    int pid = 0;

    if (!w->pasv_set && !w->port_set) {
        SEND_FTP(425, NULL);
        return;
    }
    if (ftp_order->parameters == NULL || ftp_order->parameters[1] == NULL) {
        SEND_FTP_C(550, "STOR command format unrecognized.");
        return;
    }
    if ((pid = MY_FORK(w)) == -1) {
        SEND_FTP_C(425, "Fork problem.");
    }
    if (pid == 0)
        stor(w, ftp_order);
    close_pasv_port(w);
}