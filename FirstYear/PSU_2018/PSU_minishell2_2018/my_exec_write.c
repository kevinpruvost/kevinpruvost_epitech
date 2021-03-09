/*
** EPITECH PROJECT, 2019
** my_exec_write.c
** File description:
** my_exec for > & >>
*/

#include "my.h"

int open_file_program_write(mini_t *w, int opt)
{
    int fd = 0;
    struct stat pstat;

    if (w->to_runs->next == NULL || w->to_runs->next->to_run[0] == 0) {
        my_putstr_error("Missing name for redirect.\n");
        return (-1);
    }
    (opt == 0) ? (fd = open(w->to_runs->next->to_run,
    O_RDWR | O_TRUNC | O_CREAT, S_IRWXU)) :
    (fd = open(w->to_runs->next->to_run, O_RDWR | O_APPEND));
    if (fd == -1) {
        stat(w->to_runs->next->to_run, &pstat);
        if ((S_ISDIR(pstat.st_mode)) == 1) {
            my_putstr_error(w->to_runs->next->to_run);
            my_putstr_error(": Is a directory.\n");
        }
        return (-1);
    }
    return (fd);
}

int program_grep(int fd_file, mini_t *w)
{
    int id = w->use_id - 1;
    char *cnt = create_string(0);
    char *line = create_string(1);

    (id < 0) ? (id = 0) : (0);
    for (int err = read(w->fd[id][0], line, 1); err > 0;) {
        if (cnt[0] == 0)
            cnt = my_strcpy(line);
        else {
            cnt = str_add(cnt, line);
        }
        err = read(w->fd[id][0], line, 1);
    }
    write(fd_file, cnt, my_strlen(cnt));
    free(cnt);
}

int program_write(char *to_run, char *to_runt, char **args, mini_t *w)
{
    int fd_file = open_file_program_write(w, 0);
    int parent = getpid();

    if (fd_file == -1)
        return (84);
    if (w->piped == 1) {
        program_grep(fd_file, w);
        return (0);
    }
    w->pid = fork();
    if (w->pid == 0 && dup2(fd_file, 1) != -1) {
        if (identify_cmd(w->to_runs_technical->to_run) == 1)
            special_programs(w->to_runs->to_run, w->args->args, w);
        else {
            execve(to_runt, args, w->env);
            my_put_errno(w);
        }
        exit(0);
    } else
        wait(NULL);
}

int program_write_end(char *to_run, char *to_runt, char **args, mini_t *w)
{
    int fd_file = open_file_program_write(w, 1);
    int parent = getpid();

    if (fd_file == -1)
        return (84);
    if (w->piped == 1) {
        program_grep(fd_file, w);
        return (0);
    }
    w->pid = fork();
    if (w->pid == 0 && dup2(fd_file, 1) != -1) {
        if (identify_cmd(w->to_runs_technical->to_run) == 1)
            special_programs(w->to_runs->to_run, w->args->args, w);
        else {
            execve(to_runt, args, w->env);
            my_put_errno(w);
        }
        exit(0);
    } else
        wait(NULL);
}

void launch_program_write(mini_t *w)
{
    char *sep =	w->seps->sep;
    char *to_run = w->to_runs->to_run;
    char *to_run_technical = w->to_runs_technical->to_run;
    char **env = w->env;
    char **args = w->args->args;

    if (my_strcmp(sep, ">") == 1)
        program_write(to_run, to_run_technical, args, w);
    if (my_strcmp(sep, ">>") == 1)
        program_write_end(to_run, to_run_technical, args, w);
}
