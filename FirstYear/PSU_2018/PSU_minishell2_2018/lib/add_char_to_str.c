/*
** EPITECH PROJECT, 2019
** add_char_to_str.c
** File description:
** add char to str
*/

#include "my.h"

char *add_char_to_str(char *str, int pos, char c)
{
    char *nstr;

    if (pos < 0 || pos >= my_strlen(str))
        return (str);
    nstr = create_string(my_strlen(str) + 2);
    for (int i = 0; i < pos; i++)
        nstr[i] = str[i];
    nstr[pos] = c;
    for (int i = pos; str[i] != 0; i++)
        nstr[i+1] = str[i];
    free(str);
    return (nstr);
}
