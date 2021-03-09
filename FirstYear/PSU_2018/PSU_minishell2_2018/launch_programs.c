/*
** EPITECH PROJECT, 2019
** launch_programs.c
** File description:
** launch programs
*/

#include "my.h"

int launch_program(char *to_run, char *err, char **av, mini_t *w)
{
    int parent = getpid();

    if (identify_cmd(to_run) == 0 && access(to_run, F_OK) == 0 &&
    is_reg_file(to_run) == 1) {
        w->pid = fork();
        if (w->pid == 0) {
            (w->use_id != 0) ? (dup2m(w, 0)) : (0);
            execve(to_run, av, w->env);
            my_put_errno(w);
        } else {
            wait(&parent);
            (parent == 139) ? (my_putstr_error("Segmentation fault\n")) : (0);
        }
    } else if (identify_cmd(to_run) == 0) {
        my_putstr_error(str_add(err, ": Command not found.\n"));
    } else
        special_programs(to_run, av, w);
    w->piped = 0;
}

void iteration_launch_programs_for(mini_t *w)
{
    if (w->to_runs != NULL)
        w->to_runs = w->to_runs->next;
    if (w->to_runs_technical != NULL)
        w->to_runs_technical = w->to_runs_technical->next;
    if (w->args != NULL)
        w->args = w->args->next;
    (w->seps != NULL) ? (w->seps = w->seps->next) : (0);
}

void launch_programs_for(mini_t *w)
{
    for (int i = 0; i < 50; pipe(w->fd[i]), i++);
    for (; w->to_runs != NULL; w->progs++) {
        if (w->seps == NULL || my_strcmp(w->seps->sep, ";") == 1)
            launch_program(w->to_runs_technical->to_run,
            w->to_runs->to_run, w->args->args, w);
        if (w->seps != NULL && my_strcmp(w->seps->sep, "|") == 1)
            launch_program_pipe(w);
        if (w->seps != NULL && w->seps->sep[0] == '<') {
            launch_program_read(w);
            iteration_launch_programs_for(w);
        } if (w->seps != NULL && w->seps->sep[0] == '>') {
            launch_program_write(w);
            iteration_launch_programs_for(w);
        }
        if (w->error == 84)
            iteration_error(w);
        iteration_launch_programs_for(w);
    }
}

int launch_programs(mini_t *w)
{
    seps_t *seps = w->seps;
    to_runs_t *to_runs = w->to_runs;
    to_runs_t *to_runs_t = w->to_runs_technical;
    args_t *args = w->args;

    w->use_id = 0;
    if (error_launch_prog(w) == 84)
        return (84);
    launch_programs_for(w);
    w->seps = seps;
    w->to_runs = to_runs;
    w->to_runs_technical = to_runs_t;
    w->args = args;
    dup(0);
    dup(1);
    close(w->fd[0][0]);
    close(w->fd[0][1]);
    for (; w->progs > 0; w->progs--)
        wait(NULL);
}
