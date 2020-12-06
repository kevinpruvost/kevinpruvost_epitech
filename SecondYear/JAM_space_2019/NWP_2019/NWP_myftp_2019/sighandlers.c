/*
** EPITECH PROJECT, 2020
** sighandlers.c
** File description:
** signal handlers
*/

#include "main.h"

void signal_remover(int sig)
{
}

void signal_int_handler(int sig)
{
    UNBLOCK_SIGNALS;
    kill(0, SIGUSR1);
}

void signal_usr1_handler(int sig)
{
    ftp_loopy_loop(NULL, false);
}

static int set_signals(struct sigaction * act, sigset_t * mask, sigset_t * orig)
{
    sigemptyset(mask);
    sigaddset(mask, SIGUSR1);
    sigemptyset(orig);
    sigaddset(orig, SIGUSR1);
    sigaddset(orig, SIGINT);
    return EXIT_SUCCESS;
}

int bsignals(int mode)
{
    static sigset_t mask;
    static sigset_t orig_mask;
    static struct sigaction act;

    if (set_signals(&act, &mask, &orig_mask) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (mode == 0) {
        if (sigprocmask(SIG_BLOCK, &mask, &orig_mask) < 0) {
            fprintf(stderr, "Sigprocmask error.\n");
            return EXIT_FAILURE;
        }
    } else if (mode == 1) {
        if (sigprocmask(SIG_UNBLOCK, &orig_mask, NULL) < 0) {
            fprintf(stderr, "Sigprocmask error.\n");
            return EXIT_FAILURE;
        }
    } else
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}