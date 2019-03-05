/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main funcs
*/

#include "my.h"

void display_main(char *to_run, char **av)
{
    int i = 0;

    my_putstr("Program name: ");
    my_putstr(to_run);
    my_putstr("\nNb args: ");
    for (; av[i] != NULL; i++);
    my_put_nbr(i);
}

void display_process(pid_t pid)
{
    if (pid != 0) {
        my_putstr("\nPID: ");
        my_put_nbr(getpid());
    } else {
        my_putstr("\nChild PID: ");
        my_put_nbr(getpid());
        my_putstr("\n");
    }
}

int launch_program(pid_t pid, char *to_run, char **av, char **env)
{
    int parent = getpid();
    char *error = str_add(to_run, ": Command not found.\n");

    if (identify_cmd(to_run) == 0 && access(to_run, X_OK) == 0 &&
    is_reg_file(to_run) == 1) {
        pid = fork();
        if (pid == 0) {
            execve(to_run, av, env);
            perror(NULL);
        } else {
            wait(&parent);
            if (parent == 139)
                my_putstr_error("Segmentation fault\n");
        }
    } else if (identify_cmd(to_run) == 0) {
        my_putstr_error(error);
    }
    free(error);
}

int identify_cmd(char *str)
{
    int id = 0;

    if (is_str(str, "setenv") == 1)
        id = 1;
    if (is_str(str, "unsetenv") == 1)
        id = 1;
    if (is_str(str, "exit") == 1)
        id = 1;
    if (is_str(str, "env") == 1 || is_str(str, "echo") == 1)
        id = 1;
    if (is_str(str, "cd") == 1)
        id = 1;
    return (id);
}

char **my_exec(int ac, char *str, char **env)
{
    char *to_run;
    char **args;
    pid_t pid;

    if (str == NULL) {
        my_putstr("exit\n");
        exit(0);
    }
    if (ac < 2 || str == NULL || str[0] == 0)
        return (env);
    args = args_for_my_exec(args, str, env);
    if (args == NULL)
        return (env);
    to_run = str_for_my_exec(args[0], env);
    args[0] = to_run;
    launch_program(pid, to_run, args, env);
    env = special_programs(to_run, args, env);
    free_my_exec(to_run, args);
    return (env);
}
