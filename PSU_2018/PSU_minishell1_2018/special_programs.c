/*
** EPITECH PROJECT, 2019
** special_programs.c
** File description:
** progs spe
*/

#include "my.h"

void env_func(char *to_run, char **args, char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        my_putstr(env[i]);
        my_putstr("\n");
    }
}

char **setenv_func(char *to_run, char **args, char **env)
{
    int i = my_arraylen(args);
    char *str;

    (i == 1) ? (env_func(to_run, args, env)) : (0);
    if (i == 1)
        return (env);
    if (i == 2)
        if (env_var_exist(env, args[1]) == 1) {
            replace_env_setenv(env, str_add(args[1], "="), args[1]);
        } else
            env = str_add_to_array(str_add(args[1], "="), env);
    else if (i == 3) {
        str = str_add(str_add(args[1], "="), args[2]);
        if (env_var_exist(env, args[1]) == 1) {
            replace_env_setenv(env, str, args[1]);
        } else
            env = str_add_to_array(str, env);
    } else
        my_putstr_error("setenv: Too many arguments.\n");
    return (env);
}

char **unsetenv_func(char *to_run, char **args, char **env)
{
    int i = 0;

    for (; args[i] != NULL; i++);
    if (i >= 2) {
        for (; i > 1; i--)
            unsetenv_function(env, args[i-1]);
    } else
        my_putstr_error("unsetenv: Too few arguments.\n");
    return (env);
}

char **cd_func(char *to_run, char **args, char **env)
{
    int i = my_arraylen(args);
    char *home = search_env("HOME", env);
    char *oldpwd = search_env("OLDPWD", env);
    char *pwd = search_env("PWD", env);
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
    (error == 0) ? (env = pwd_oldpwd(env, pwd)) : (0);
    return (env);
}

char **special_programs(char *to_run, char **args, char **env)
{
    env = special_programs2(to_run, args, env);
    if (is_str(to_run, "setenv") == 1)
        if (setenv_alpha(args) == 1)
            env = setenv_func(to_run, args, env);
    if (is_str(to_run, "unsetenv") == 1)
        env = unsetenv_func(to_run, args, env);
    if (is_str(to_run, "env") == 1)
        env_func(to_run, args, env);
    if (is_str(to_run, "echo") == 1) {
        if (my_arraylen(args) > 1)
            my_putstr(str_add(args[1], "\n"));
        else
            my_putstr("\n");
    }
    return (env);
}
