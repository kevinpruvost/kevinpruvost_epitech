/*
** EPITECH PROJECT, 2020
** multi_tok.c
** File description:
** m
*/

#include "main.h"

char * multi_tok(char *input, const char *delimiter)
{
    static char *string;
    char * temp = NULL;
    char * end = NULL;

    if (input != NULL)
        string = input;
    if (string == NULL)
        return string;
    end = strstr(string, delimiter);
    if (end == NULL) {
        temp = (string != NULL && string[0] != 0) ? strdup(string) : NULL;
        string = NULL;
        return temp;
    }
    temp = strdup(string);
    end += strlen(delimiter);
    temp[end - string] = 0;
    string = end;
    return temp;
}