/*
** EPITECH PROJECT, 2019
** get_add_info.c
** File description:
** get add info
*/

#include "my.h"

char *get_add_info(char *line)
{
    int i = 0;
    char *msg = create_string(my_strlen(line));

    for (; line[i] != 0 && line[i+1] != 0; i++);
    for (; line[i] != ':'; i--);
    i++;
    for (int j = 0; line[i] != 0; i++, j++)
        msg[j] = line[i];
    return (msg);
}
