/*
** EPITECH PROJECT, 2019
** is_env_display.c
** File description:
** is env display
*/

#include "my.h"

char *cut_env(char *buffer)
{
    char *buff = malloc(sizeof(char) * my_strlen(buffer));

    for (int i = 0; buffer[i] != 0 && buffer[i] != '='; i++)
        buff[i] = buffer[i];
    return (buff);
}

int is_env_display(char **env)
{
    char *buffer;

    for (int i = 0; env[i] != NULL; i++) {
        buffer = cut_env(env[i]);
        if (is_str(env[i], "DISPLAY=:0.0") == 1) {
            free(buffer);
            return (1);
        }
        free(buffer);
    }
    return (0);
}
