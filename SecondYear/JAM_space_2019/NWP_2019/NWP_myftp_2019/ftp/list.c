/*
** EPITECH PROJECT, 2020
** list.c
** File description:
** list
*/

#include "main.h"

static char * make_msg(client_t * client, ftp_order_t * w)
{
    char * msg = NULL;
    int size = strlen("ls -l  | grep -v ^d | grep -v ^total");

    for (int i = 1; w->parameters != NULL && w->parameters[i] != NULL; ++i)
        size += strlen(w->parameters[i]) + 1;
    msg = malloc(sizeof(char) * (size + 1));
    strcpy(msg, "ls -l ");
    for (int i = 1; w->parameters != NULL && w->parameters[i] != NULL; ++i) {
        strcat(msg, w->parameters[i]);
        strcat(msg, " ");
    }
    return msg;
}

static int send_list(client_t * client, ftp_order_t * w)
{
    int fd_cl = open_pasv_port(client);
    char * msg = NULL;
    FILE * file = NULL;
    char str[BUFFER_SIZE] = {0};

    if (fd_cl == -1 || chdir(client->path) == -1) {
        my_send_custom(client->fd, 425, "Problem with connection.");
        return EXIT_FAILURE;
    }
    my_send(client->fd, 150, NULL);
    msg = make_msg(client, w);
    strcat(msg, " | grep -v ^total");
    file = popen(msg, "r");
    for (; fgets(str, BUFFER_SIZE - 1, file); memset(str, 0, BUFFER_SIZE))
        write(fd_cl, str, strlen(str));
    fclose(file);
    close(fd_cl);
    close_pasv_port(client);
    free(msg);
    return EXIT_SUCCESS;
}

void ftp_list(client_t * w, ftp_order_t * ftp)
{
    int pid = 0;

    if (!w->pasv_set && !w->port_set) {
        SEND_FTP(425, NULL);
        return;
    }
    if ((pid = MY_FORK(w)) == -1) {
        SEND_FTP_C(425, "Fork problem.");
        return;
    }
    if (pid == 0) {
        if (send_list(w, ftp) == EXIT_FAILURE)
            return;
        SEND_FTP(226, NULL);
    }
    close_pasv_port(w);
}