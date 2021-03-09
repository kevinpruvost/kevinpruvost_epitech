/*
** EPITECH PROJECT, 2019
** my_exec_read2.c
** File description:
** my_exec_read2
*/

#include "my.h"

int identify_order_program(mini_t *w)
{
    seps_t *seps = w->seps;

    if (w->seps->next == NULL || w->seps->next->sep[0] == 0 ||
        w->seps->next->sep[0] == ';')
        return (0);
    return (1);
}

void program_file2(mini_t *w, char *cnt)
{
    w->pid = fork();
    if (w->pid == 0) {
        dup2m(w, 1);
        my_printf("%s", cnt);
        exit(0);
    } else
        wait(NULL);
}

int program_file(char *to_run, char *to_runt, char **args, mini_t *w)
{
    char *cnt;
    int parent = getpid();
    int id = identify_order_program(w);

    if (w->to_runs->next != NULL)
        cnt = load_file_in_mem(w->to_runs->next->to_run);
    else {
        my_putstr_error("Missing name for redirect.\n");
        return (84);
    }
    program_file2(w, cnt);
    closem(w, 1);
    w->pid = fork();
    if (w->pid == 0) {
        dup2m(w, id);
        execve(to_runt, args, w->env);
        my_put_errno(w);
    } else
        wait(&parent);
    (id == 1) ? (closem(w, 1)) : (0);
}
