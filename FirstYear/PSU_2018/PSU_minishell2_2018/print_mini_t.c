/*
** EPITECH PROJECT, 2019
** print_mini_t.c
** File description:
** print mini struct
*/

#include "my.h"

void print_mini_t2(mini_t *w)
{
    to_runs_t *to_runsm = w->to_runs_technical;

    my_printf("\nTo_runs_technical :\n");
    for (; to_runsm != NULL; to_runsm = to_runsm->next)
        my_printf("[%s]\n", to_runsm->to_run);
}

void print_mini_t(mini_t *w)
{
    to_runs_t *to_runsm = w->to_runs;

    my_printf("To_runs :\n");
    for (; to_runsm != NULL; to_runsm = to_runsm->next)
        my_printf("[%s]\n", to_runsm->to_run);
    print_mini_t2(w);
    my_printf("\nArgs :\n");
    for (args_t *argsm = w->args; argsm != NULL; argsm = argsm->next) {
        my_printf("[");
        for (int i = 0; argsm->args[i] != NULL; i++) {
            my_printf("%s", argsm->args[i]);
            if (argsm->args[i+1] != NULL)
                my_printf(",  ");
        }
        my_printf("]\n");
    }
    my_printf("\nSeparators :\n");
    for (seps_t *sepm = w->seps; sepm != NULL; sepm = sepm->next)
        my_printf("[%s]\t", sepm->sep);
    my_printf("\n");
}
