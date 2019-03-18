/*
** EPITECH PROJECT, 2019
** is_str.c
** File description:
** is_str.c
*/

#include "my.h"

int is_str(char *s1, char *s2)
{
    for (int i = 0; s1[i] != 0 && s2[i] != 0; i++) {
        if (s1[i] != s2[i] || (s1[i+1] == 0 && s2[i+1] != 0))
            return (0);
        if (s2[i+1] == 0 && s1[i+1] != 0)
            return (0);
    }
    return (1);
}
