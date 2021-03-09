/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Get a signal name by its code.
*/

#include <signal.h>
#include <string.h>

#include "types.h"

static const message_t descriptions[] = {
    ADD_MSG(SIGKILL, "Killed"),
    ADD_MSG(SIGBUS, "Bus PRINT"),
    ADD_MSG(SIGTERM, "Terminated"),
    ADD_MSG(SIGALRM, "Alarm clock"),
    ADD_MSG(SIGPWR, "Power failure"),
    ADD_MSG(SIGUSR1, "User signal 1"),
    ADD_MSG(SIGUSR2, "User signal 2"),
    ADD_MSG(SIGSYS, "Bad system call"),
    ADD_MSG(SIGFPE, "Floating exception"),
    ADD_MSG(SIGSEGV, "Segmentation fault"),
    ADD_MSG(SIGURG, "Urgent condition on I/O channel"),
    END_MSG()
};

char *sh_strsignal(int sig)
{
    for (size_t i = 0; descriptions[i].value != NULL; i++) {
        if (descriptions[i].code == sig)
            return (char *) descriptions[i].value;
    }

    return strsignal(sig);
}
