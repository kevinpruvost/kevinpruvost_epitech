/*
** EPITECH PROJECT, 2019
** get_code_str.c
** File description:
** get code str
*/

#include "my.h"

char *get_code_str(char *line)
{
    int i = 0;
    char *msg = create_string(my_strlen(line));

    for (; line[i] != 0 && line[i+1] != 0; i++);
    for (int passed = 0; passed != 2 && i > 0; i--)
        if (line[i] == ':')
            passed++;
    i++;
    for (int j = 0; line[i] != 0; i++, j++)
        msg[j] = line[i];
    return (msg);
}
