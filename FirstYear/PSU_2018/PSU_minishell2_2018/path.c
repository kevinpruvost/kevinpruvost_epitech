/*
** EPITECH PROJECT, 2019
** path.c
** File description:
** for path funcs
*/

#include "my.h"

char **remove_str_from_array(char **env, int n)
{
    if (env[n+1] == NULL)
        env[n] = NULL;
    else {
        for (int i = n; env[i+1] != NULL; i++) {
            env[i] = env[i+1];
            if (env[i+2] == NULL)
                env[i+1] = NULL;
        }
    }
    return (env);
}

char *check_identify(char *envs)
{
    char *check = malloc(sizeof(char) * my_strlen(envs + 1));

    for (int i = 0; envs[i] != 0 && envs[i] != '='; i++) {
        check[i] = envs[i];
        check[i+1] = 0;
    }
    return (check);
}

char **unsetenv_function(char **env, char *arg)
{
    char *check;

    for (int i = 0; env[i] != NULL; i++) {
        check = check_identify(env[i]);
        if (my_strcmp(check, arg) == 1) {
            env = remove_str_from_array(env, i);
        }
        free(check);
    }
    return (env);
}

char **path_find(char **args, int n, char **env)
{
    char *check;
    char *to_replace;

    args[n]++;
    for (int i = 0; env[i] != NULL; i++) {
        check = check_identify(env[i]);
        if (my_strcmp(check, args[n]) == 1) {
            to_replace = env_value(env[i]);
            args[n] = to_replace;
        }
        free(check);
    }
    return (args);
}

char **path_detect(char **args, char **env)
{
    for (int i = 0; args[i] != NULL; i++)
        if (args[i][0] == '$' && my_strlen(args[i]) > 1)
            args = path_find(args, i, env);
    return (args);
}
