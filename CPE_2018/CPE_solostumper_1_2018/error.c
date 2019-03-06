/*
** EPITECH PROJECT, 2019
** error.c
** File description:
** error func
*/

#include "my.h"

int error_management(char *string)
{
    int valid_char = 0;
    
    for (int i = 0; string[i] != 0; i++) {
        if (string[i] != '\n' && string[i] != ' ' && string[i] != '\t')
            valid_char++;
        if (string[i] < 32)
            valid_char--;
    }
    return (valid_char);
}
