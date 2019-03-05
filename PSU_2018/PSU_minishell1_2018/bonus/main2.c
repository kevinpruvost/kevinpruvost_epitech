/*
** EPITECH PROJECT, 2019
** main2.c
** File description:
** more funcs for main.c in bonus
*/

#include "my.h"
#include "bonus.h"

int check_variable(char *env, char *var)
{
    for (int i = 0; var[i] != 0 && env[i] != 0; i++) {
        if (var[i] != env[i])
            return (0);
    }
    return (1);
}

char *search_name(char **env)
{
    char *name;
    int p = -1;

    for (int i = 0; env[i] != NULL && p == -1; i++)
        if (check_variable(env[i], "LOGNAME=") == 1)
            p = i;
    if (p == -1)
        return (NULL);
    name = malloc(sizeof(char) * (my_strlen(env[p]) + 1));
    for (int i = 8, j = 0; env[p][i] != 0; i++, j++) {
        name[j] = env[p][i];
        name[j+1] = 0;
    }
    return (name);
}

char *search_computer(char **env)
{
    char *computer;
    int p = -1;

    for (int i = 0; env[i] != NULL && p == -1; i++)
        if (check_variable(env[i], "HOSTNAME=") == 1)
            p = i;
    if (p == -1)
        return (NULL);
    computer = malloc(sizeof(char) * (my_strlen(env[p]) + 1));
    for (int i = 9, j = 0; env[p][i] != 0 && env[p][i] != '.'; i++, j++) {
        computer[j] = env[p][i];
        computer[j+1] = 0;
    }
    return (computer);
}

char *format_dir(char *dir)
{
    int p = -1;
    char *new_dir;

    if (dir == NULL)
        return (NULL);
    new_dir = malloc(sizeof(char) * my_strlen(dir));
    for (int i = 0; dir[i] != 0; i++)
        if (dir[i] == '/')
            p = i;
    for (int i = p + 1, j = 0; dir[i] != 0; i++, j++) {
        new_dir[j] = dir[i];
        new_dir[j+1] = 0;
    }
    free(dir);
    return (new_dir);
}
