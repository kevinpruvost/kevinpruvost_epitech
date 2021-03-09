/*
** EPITECH PROJECT, 2019
** my_exec_read.c
** File description:
** my_exec for read
*/

#include "my.h"

char *read_msg(char *stop)
{
    char *line;
    char *msg = malloc(sizeof(char));

    my_putstr("? ");
    line = get_next_line(0);
    msg[0] = 0;
    for (; my_strcmp(stop, line) == 0; line = get_next_line(0)) {
        my_putstr("? ");
        msg = str_add(msg, line);
        msg = str_add(msg, "\n");
    }
    return (msg);
}

void program_keyboard2(mini_t *w, char *line)
{
    w->pid = fork();
    if (w->pid == 0) {
        dup2m(w, 1);
        my_printf("%s", line);
        exit(0);
    } else
        wait(NULL);
    closem(w, 1);
    w->pid = fork();
}

int program_keyboard(char *to_run, char *to_runt, char **args, mini_t *w)
{
    int parent = getpid();
    char *line;
    int id = identify_order_program(w);

    if (w->to_runs->next != NULL)
        line = read_msg(w->to_runs->next->to_run);
    else {
        my_putstr_error("Missing name for redirect.\n");
        return (84);
    }
    program_keyboard2(w, line);
    if (w->pid == 0) {
        dup2m(w, id);
        execve(to_runt, args, w->env);
        my_put_errno(w);
    } else {
        wait(&parent);
        (parent == 139) ? (my_putstr_error("Segmentation fault\n")) : (0);
    }
    (id == 1) ? (closem(w, 1)) : (0);
}

void launch_program_read(mini_t *w)
{
    char *sep = w->seps->sep;
    char *to_run = w->to_runs->to_run;
    char *to_run_technical = w->to_runs_technical->to_run;
    char **env = w->env;
    char **args = w->args->args;

    w->piped = 1;
    if (my_strcmp(sep, "<") == 1) {
        program_file(to_run, to_run_technical, args, w);
    }
    if (my_strcmp(sep, "<<") == 1)
        program_keyboard(to_run, to_run_technical, args, w);
}
