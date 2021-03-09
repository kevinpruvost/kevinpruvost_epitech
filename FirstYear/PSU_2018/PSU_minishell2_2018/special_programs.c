/*
** EPITECH PROJECT, 2019
** special_programs.c
** File description:
** progs spe
*/

#include "my.h"

void env_func(char *to_run, char **args, mini_t *w)
{
    int loc = 1;

    for (int i = 0; w->env[i] != NULL; i++) {
        my_putstr_fd(w->env[i], loc);
        my_putstr_fd("\n", loc);
    }
}

int setenv_func(char *to_run, char **args, mini_t *w)
{
    int i = my_arraylen(args);
    char *str;

    (i == 1) ? (env_func(to_run, args, w)) : (0);
    if (i == 1)
        return (0);
    if (i == 2)
        if (env_var_exist(w->env, args[1]) == 1) {
            replace_env_setenv(w->env, str_add(args[1], "="), args[1]);
        } else
            w->env = str_add_to_array(str_add(args[1], "="), w->env);
    else if (i == 3) {
        str = str_add(str_add(args[1], "="), args[2]);
        if (env_var_exist(w->env, args[1]) == 1) {
            replace_env_setenv(w->env, str, args[1]);
        } else
            w->env = str_add_to_array(str, w->env);
    } else
        my_putstr_error("setenv: Too many arguments.\n");
}

void unsetenv_func(char *to_run, char **args, mini_t *w)
{
    int i = 0;

    for (; args[i] != NULL; i++);
    if (i >= 2) {
        for (; i > 1; i--)
            unsetenv_function(w->env, args[i-1]);
    } else
        my_putstr_error("unsetenv: Too few arguments.\n");
}

void cd_func(char *to_run, char **args, mini_t *w)
{
    int i = my_arraylen(args);
    char *home = search_env("HOME", w->env);
    char *oldpwd = search_env("OLDPWD", w->env);
    char *pwd = search_env("PWD", w->env);
    int error = 0;
    char *error_str;

    if (i == 2)
        error_str = str_add(args[1], ": No such file or directory.\n");
    else if (i == 1)
        error_str = ": No such file or directory.\n";
    (i == 1) ? (error = chdir(home)) : (0);
    if (i == 2 && args[1][0] == '-' && args[1][1] == 0)
        (oldpwd == NULL) ? (error = -2) : (error = chdir(oldpwd));
    else if (i == 2)
        error = chdir(args[1]);
    (error == -1) ? (my_putstr_error(error_str)) : (0);
    (error == -2) ? (my_putstr_error(": No such file or directory.\n")) : (0);
    (error == 0) ? (pwd_oldpwd(w, pwd)) : (0);
}

void special_programs(char *to_run, char **args, mini_t *w)
{
    special_programs2(to_run, args, w);
    if (my_strcmp(to_run, "setenv") == 1)
        if (setenv_alpha(args) == 1)
            setenv_func(to_run, args, w);
    if (my_strcmp(to_run, "unsetenv") == 1)
        unsetenv_func(to_run, args, w);
    if (my_strcmp(to_run, "env") == 1)
        env_func(to_run, args, w);
    if (my_strcmp(to_run, "echo") == 1) {
        if (my_arraylen(args) > 1)
            my_putstr(str_add(args[1], "\n"));
        else
            my_putstr("\n");
    }
}
