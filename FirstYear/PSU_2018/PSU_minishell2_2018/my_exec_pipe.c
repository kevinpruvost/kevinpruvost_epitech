/*
** EPITECH PROJECT, 2019
** my_exec_pipe.c
** File description:
** my exec for pipes
*/

#include "my.h"

void launch_program_pipe_1(mini_t *w)
{
    w->pid = fork();
    if (w->pid == 0) {
        dup2m(w, 1);
        execve(w->to_runs_technical->to_run, w->args->args, w->env);
        my_put_errno(w);
        exit(0);
    } else
        wait(NULL);
    closem(w, 1);
}

void launch_program_pipe(mini_t *w)
{
    char *error = str_add(w->to_runs->to_run, ": Command not found.\n");

    if (identify_cmd(w->to_runs_technical->to_run) == 0
        && access(w->to_runs_technical->to_run, F_OK) == 0 &&
        is_reg_file(w->to_runs_technical->to_run) == 1) {
        launch_program_pipe_1(w);
        w->piped = 1;
    } else if (identify_cmd(w->to_runs_technical->to_run) == 0) {
        my_putstr_error(error);
    } else {
        if ((w->pid = fork()) == 0) {
            dup2m(w, 1);
            special_programs(w->to_runs_technical->to_run, w->args->args, w);
            exit(0);
        } else
            wait(NULL);
        closem(w, 1);
    }
    w->piped = 1;
    free(error);
}
