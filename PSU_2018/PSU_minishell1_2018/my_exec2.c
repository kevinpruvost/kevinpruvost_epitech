/*
** EPITECH PROJECT, 2019
** my_exec2.c
** File description:
** my_exec subfuncs
*/

#include "my.h"

int check_path(char *env)
{
    char *path = "PATH=";

    for (int i = 0; path[i] != 0; i++) {
        if (env[i] != path[i])
            return (0);
    }
    return (1);
}

char **path_values(char *env)
{
    char **arr = malloc(sizeof(char *) * 10);
    int i = 0;

    for (int n = 0; n < 5; n++, env++);
    for (int j = 0; env[j] != 0; i++) {
        arr[i] = malloc(sizeof(char) * (my_strlen(env) + 1));
        for (int x = 0; env[j] != ':' && env[j] != 0; j++, x++) {
            arr[i][x] = env[j];
            arr[i][x+1] = '/';
            arr[i][x+2] = '\0';
        }
        (env[j] == ':') ? (j++) : (0);
    }
    arr[i] = NULL;
    return (arr);
}

char *str_for_my_exec(char *str, char **env)
{
    int n_path = -1;
    char **path;
    char *test;

    for (int i = 0; env[i] != NULL && n_path == -1; i++)
        if (check_path(env[i]) == 1)
            n_path = i;
    if (n_path == -1)
        return (str);
    str = str_sk(str);
    path = path_values(env[n_path]);
    if (str[0] != '.' && str[0] != '/' && identify_cmd(str) == 0)
        for (int i = 0; path[i] != NULL; i++) {
            test = str_add(path[i], str);
            (access(test, F_OK) == 0) ? (str = test) : (free(test));
        }
    free_path(path);
    return (str);
}

char **args_for_my_exec(char **args, char *str, char **env)
{
    str = str_sk(str);
    if (str == NULL)
        return (NULL);
    if (str[0] == ' ' && str[1] == 0)
        return (NULL);
    args = str_to_word_array(str);
    args = path_detect(args, env);
    return (args);
}
