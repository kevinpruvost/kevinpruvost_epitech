/*
** EPITECH PROJECT, 2020
** sighandlers2.c
** File description:
** sighandlers
*/

#include "main.h"

void signal_handler(int sig)
{
    kill(0, SIGUSR1);
}

void signal_handler2(int sig)
{
    fprintf(stderr, "Destroying child %d.\n", getpid());
    ftp_loopy_loop(NULL, false);
}