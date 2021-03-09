/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main funcs
*/

#include "my.h"

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

int identify_cmd(char *str)
{
    int id = 0;

    if (my_strcmp(str, "setenv") == 1)
        id = 1;
    if (my_strcmp(str, "unsetenv") == 1)
        id = 1;
    if (my_strcmp(str, "exit") == 1)
        id = 1;
    if (my_strcmp(str, "env") == 1)
        id = 1;
    if (my_strcmp(str, "cd") == 1)
        id = 1;
    return (id);
}

int error_str(char *str)
{
    if (my_strcmp(str, "|") == 1) {
        my_putstr_error("Invalid null command.\n");
        return (84);
    }
    if (str[0] == '<' || str[0] == '>') {
        my_putstr_error("Missing name for redirect.\n");
        return (84);
    }
    return (0);
}

char **my_exec(int ac, char *str_b, char **env)
{
    pid_t pid;
    mini_t *w;
    char *str = my_strcpy(str_b);

    if (str == NULL || my_strcmp("exit", str) == 1) {
        my_putstr("exit\n");
        exit(0);
    }
    if (ac < 2 || str == NULL || str[0] == 0 || error_str(str) == 84)
        return (env);
    str = str_sk(str);
    if (error_str(str) == 84)
        return (env);
    w = parse_mini(str, env);
    launch_programs(w);
    env = w->env;
    free_mini_t(w);
    return (env);
}
