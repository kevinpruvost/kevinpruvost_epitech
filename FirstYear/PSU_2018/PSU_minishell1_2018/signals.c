/*
** EPITECH PROJECT, 2019
** signals.c
** File description:
** signals ctrl c ctrl z
*/

#include "my.h"

void sigstop(int p)
{
    pid_t my_pid = getpid();

    my_putstr("\n");
    if (my_pid != 0) {
        my_putstr("$> ");
    }
}

void sigkill(int p)
{
    pid_t my_pid = getpid();

    if (my_pid == 0)
        kill(my_pid, SIGKILL);
}
