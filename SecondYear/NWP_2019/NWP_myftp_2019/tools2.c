/*
** EPITECH PROJECT, 2020
** tools2.c
** File description:
** tools
*/

#include "main.h"

void str_to_upper(char * line)
{
    for (int i = 0; line[i] != 0; ++i) {
        line[i] = toupper(line[i]);
    }
}

char * raw_char(char c)
{
    if (c == '\n')
        return "\\n";
    if (c == '\r')
        return "\\r";
    if (c == '\t')
        return "\\t";
    return NULL;
}

void print_raw_str(char * line)
{
    fprintf(stderr, "Raw string : [");
    for (int i = 0; line[i] != 0; ++i) {
        if (raw_char(line[i]) == NULL)
            fprintf(stderr, "%c", line[i]);
        else
            fprintf(stderr, "%s", raw_char(line[i]));
    }
    fprintf(stderr, "]\n");
}

bool dir_exists(const char * path)
{
    struct stat sb;

    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        return true;
    } else
        return false;
}

void remove_first_chars(char * line, int times)
{
    while (times-- > 0) {
        for (int i = 0; line[i] != 0 && line[i+1] != 0; ++i) {
            line[i] = line[i+1];
        }
    }
}