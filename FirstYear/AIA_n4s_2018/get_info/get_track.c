/*
** EPITECH PROJECT, 2019
** get_track.c
** File description:
** get_track
*/

#include "my.h"

char *get_track(char *line)
{
    int i = 0;
    char *msg = create_string(my_strlen(line));

    for (; line[i] != 0 && line[i+1] != 0; i++);
    for (int passed = 0; passed != 2 && i > 0; i--)
        if (line[i] == ':')
            passed++;
    i++;
    if (line[i] == ':')
        i++;
    for (int j = 0; line[i] != 0 && line[i] != ':'; i++, j++)
        msg[j] = line[i];
    return (msg);
}
