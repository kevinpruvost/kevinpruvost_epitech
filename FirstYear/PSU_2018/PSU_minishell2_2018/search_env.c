/*
** EPITECH PROJECT, 2019
** search_env.c
** File description:
** search in env
*/

#include "my.h"

int is_str_env(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return (0);
    for (int i = 0; s1[i] != 0 && s2[i] != 0 && s1[i] != '='
        && s2[i] != '='; i++)
        if (s1[i] != s2[i])
            return (0);
    return (1);
}

char *search_env(char *str, char **env)
{
    int n = -1;
    int nb = my_strlen(str);
    char *s;

    for (int i = 0; env[i] != NULL && n == -1; i++) {
        if (is_str_env(str, env[i]) == 1)
            n = i;
    }
    if (n == -1)
        return (NULL);
    else {
        s = malloc(sizeof(char) * (my_strlen(env[n]) + 255));
        for (int i = 0; env[n][i] != 0; i++) {
            s[i] = env[n][i];
            s[i+1] = '\0';
        }
        for (int i = 0; i < nb + 1; i++)
            s++;
        return (s);
    }
}
