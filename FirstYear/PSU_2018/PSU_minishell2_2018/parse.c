/*
** EPITECH PROJECT, 2019
** parse.c
** File description:
** parsing funcs
*/

#include "my.h"

void error_args_deep(args_t *args)
{
    char cmp[3];
    char cmp1[3];

    cmp[0] = '"';
    cmp[1] = 0;
    cmp[2] = 0;
    cmp1[0] = 0;
    cmp1[1] = 0;
    cmp1[2] = 0;
    for (int i = 0; args->args[i] != NULL; i++)
        if (my_strcmp(args->args[i], cmp) == 1)
            args->args[i] = my_strcpy(cmp1);
}

void error_args(mini_t *w)
{
    args_t *args = w->args;

    for (; args != NULL; args = args->next) {
        error_args_deep(args);
    }
}

mini_t *parse_mini(char *str, char **env)
{
    mini_t *w = malloc(sizeof(mini_t));

    w->env = env;
    w->seps = NULL;
    w->to_runs = NULL;
    w->to_runs_technical = NULL;
    w->args = NULL;
    w->progs = 0;
    w->piped = 0;
    parse_seps(w, str);
    parse_to_runs(w, str);
    parse_args(w, str, -1);
    error_args(w);
    return (w);
}

void free_mini_t2(mini_t *w)
{
    for (to_runs_t *to_runs = w->to_runs; w->to_runs != NULL;
        to_runs = w->to_runs) {
        w->to_runs = w->to_runs->next;
        free(to_runs->to_run);
        free(to_runs);
    }
    for (args_t *args = w->args; w->args != NULL; args = w->args) {
        w->args = w->args->next;
        free(args->args);
        free(args);
    }
    free(w);
}

void free_mini_t(mini_t *w)
{
    for (seps_t *seps = w->seps; w->seps != NULL; seps = w->seps) {
        w->seps = w->seps->next;
        free(seps);
    }
    for (to_runs_t *tr = w->to_runs_technical; w->to_runs_technical != NULL;
        tr = w->to_runs_technical) {
        w->to_runs_technical = w->to_runs_technical->next;
        free(tr->to_run);
        free(tr);
    }
    free_mini_t2(w);
}
