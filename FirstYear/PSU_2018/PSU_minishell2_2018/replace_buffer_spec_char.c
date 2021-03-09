/*
** EPITECH PROJECT, 2019
** replace_buffer_spec_char.c
** File description:
** replace buffer char for spec_char.c
*/

#include "my.h"

void switch2_rcfs(char *buffer, int i)
{
    switch (buffer[i]) {
    case 'a' :
        buffer[i] = 7;
        break;
    case 'b' :
        buffer[i] = 8;
        break;
    case 't' :
        buffer[i] = 9;
        break;
    }
}

void switch1_rcfs(char *buffer, int i)
{
    switch (buffer[i]) {
    case 'n' :
        buffer[i] = 10;
    case 'v' :
        buffer[i] = 11;
    case 'f' :
        buffer[i] = 12;
    case 'r' :
        buffer[i] = 13;
    }
    switch2_rcfs(buffer, i);
}

int replace_buffer_char(char *buffer, int i)
{
    if (buffer[i+1] <= 32)
        return (0);
    remove_char_from_str(buffer, i);
    switch1_rcfs(buffer, i);
}
