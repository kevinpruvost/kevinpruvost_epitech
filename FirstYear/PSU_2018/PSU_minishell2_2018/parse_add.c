/*
** EPITECH PROJECT, 2019
** parse_add.c
** File description:
** parse add to structs
*/

#include "my.h"

int add_seps(mini_t *w, char *str)
{
    seps_t *manip = w->seps;
    seps_t *new_sep = malloc(sizeof(seps_t));

    if (new_sep == NULL)
        return (84);
    new_sep->sep = my_strcpy(str);
    new_sep->next = NULL;
    if (manip != NULL) {
        for (; manip->next != NULL; manip = manip->next);
        manip->next = new_sep;
    } else
        w->seps = new_sep;
    return (0);
}

int add_args(mini_t *w, char **str)
{
    args_t *manip = w->args;
    args_t *new_arg = malloc(sizeof(args_t));

    if (new_arg == NULL)
        return (84);
    new_arg->args = my_arrcpy(str);
    new_arg->next = NULL;
    if (manip != NULL) {
        for (; manip->next != NULL; manip = manip->next);
        manip->next = new_arg;
    } else
        w->args = new_arg;
    return (0);
}

int add_to_runs(mini_t *w, char *str)
{
    to_runs_t *man = w->to_runs;
    to_runs_t *man_t = w->to_runs_technical;
    to_runs_t *new_to_run = malloc(sizeof(to_runs_t));
    to_runs_t *new_to_run_t = malloc(sizeof(to_runs_t));

    if (new_to_run == NULL || new_to_run_t == NULL)
        return (84);
    new_to_run->to_run = my_strcpy(str);
    str = str_for_my_exec(str, w->env);
    new_to_run_t->to_run = my_strcpy(str);
    new_to_run->next = NULL;
    new_to_run_t->next = NULL;
    if (man != NULL) {
        for (; man->next != NULL; man = man->next, man_t = man_t->next);
        man->next = new_to_run;
        man_t->next = new_to_run_t;
    } else {
        w->to_runs = new_to_run;
        w->to_runs_technical = new_to_run_t;
    }
}
