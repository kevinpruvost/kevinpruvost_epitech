/*
** EPITECH PROJECT, 2019
** my_strcmp.c
** File description:
** compare 2 str
*/

#include "my.h"

int my_strcmp(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return (0);
    if (my_strlen(s1) != my_strlen(s2))
    	return (0);
    for (int i = 0; s1[i] != 0 && s2[i] != 0; i++) {
        if (s1[i] != s2[i])
            return (0);
        if (s1[i+1] == 0 && s2[i+1] != 0 && s2[i+1] != ' ')
            return (0);
        if (s2[i+1] == 0 && s1[i+1] != 0 && s1[i+1] != ' ')
            return (0);
    }
    return (1);
}
