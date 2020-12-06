/*
** EPITECH PROJECT, 2020
** fork.c
** File description:
** fork
*/

#include "main.h"

static int my_fork_create(fork_pair_t * pids, client_t * client)
{
    int i = 0;

    for (i = 0; i < CLIENT_NUMBER; ++i) {
        if (pids[i].pid == -1 || kill(pids[i].pid, 0) == -1) {
            pids[i].pid = fork();
            pids[i].client = client;
            break;
        }
    }
    if (pids[i].pid == 0) {
        for (i = 0; i < CLIENT_NUMBER; pids[i++].pid = -1);
        pids[i].pid = -1;
        pids[i].client = NULL;
        return 0;
    }
    return pids[i].pid;
}

static int my_fork_delete_alls(fork_pair_t * pids)
{
    for (int i = 0; i < CLIENT_NUMBER; ++i) {
        if (pids[i].pid != -1 && kill(pids[i].pid, 0) != -1) {
            kill(pids[i].pid, SIGUSR1);
        }
    }
    return EXIT_SUCCESS;
}

static int my_fork_delete_for_client(fork_pair_t * pids, client_t * w)
{
    for (int i = 0; i < CLIENT_NUMBER; ++i) {
        if (pids[i].pid != -1 && kill(pids[i].pid, 0) != -1 \
&& pids[i].client == w) {
            kill(pids[i].pid, SIGUSR1);
            pids[i].pid = -1;
            pids[i].client = NULL;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}

static int my_fork_base(int order, client_t * client)
{
    static fork_pair_t pids[CLIENT_NUMBER];
    static bool first = true;

    if (first) {
        first = false;
        for (int i = 0; i < CLIENT_NUMBER; ++i) {
            pids[i].pid = -1;
            pids[i].client = NULL;
        }
    }
    if (order == 0)
        return my_fork_create(pids, client);
    if (order == 1)
        return my_fork_delete_alls(pids);
    if (order == 2)
        return my_fork_delete_for_client(pids, client);
    return EXIT_FAILURE;
}

int my_fork(int order, client_t * w)
{
    return my_fork_base(order, w);
}