/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static int free_line_failure(char * line)
{
    (line != NULL) ? free(line) : 0;
    return EXIT_FAILURE;
}

static int read_server_and_client2(int distant_fd, account_t * account, \
int fd_max, fd_set * fd_set)
{
    ssize_t red = 0;
    char * line = NULL;
    int fd_p = more_pipe(1);

    if (FD_ISSET(STDIN_FD, fd_set)) {
        if ((red = my_getline(&line, STDIN_FD)) <= 0)
            return free_line_failure(line);
        if ((red = check_command(line, account)) == EXIT_FAILURE)
            return free_line_failure(line);
    } else if (FD_ISSET(fd_p, fd_set)) {
        if ((red = my_getline(&line, fd_p)) <= 0)
            return free_line_failure(line);
        more_pipe(3);
        if ((red = check_command(line, account)) == EXIT_FAILURE)
            return free_line_failure(line);
    }
    (line != NULL) ? free(line) : 0;
    return EXIT_SUCCESS;
}

int read_server_and_client(int distant_fd, account_t * account)
{
    fd_set fd_set;
    int fd_max = create_fd_set_form_clients(distant_fd, &fd_set);

    if (select(fd_max + 1, &fd_set, NULL, NULL, NULL) < 0)
        return EXIT_FAILURE;
    if (FD_ISSET(distant_fd, &fd_set)) {
        printf("\n");
        fd_max = read_server(distant_fd, account);
    } else if (read_server_and_client2(distant_fd, account, fd_max, &fd_set) \
== EXIT_FAILURE)
        return EXIT_FAILURE;
    return fd_max;
}
