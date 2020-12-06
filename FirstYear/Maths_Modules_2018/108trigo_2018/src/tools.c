/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** tools
*/

#include "my.h"

int my_strlen(char *s)
{
    int i = 0;

    for (; s[i] != 0; i++);
    return (i);
}

int my_strcmp(char *s1, char *s2)
{
    if (my_strlen(s1) != my_strlen(s2))
        return (0);
    for (int i = 0; s1[i] != 0 && s2[i] != 0; i++) {
        if (s1[i] != s2[i])
            return (0);
    }
    return (1);
}

int identify_option(char **av)
{
    char *to_cmp = av[1];

    if (my_strcmp(to_cmp, "EXP") == 1)
        return (EXP);
    if (my_strcmp(to_cmp, "COS") == 1)
        return (COS);
    if (my_strcmp(to_cmp, "SIN") == 1)
        return (SIN);
    if (my_strcmp(to_cmp, "COSH") == 1)
	return (COSH);
    if (my_strcmp(to_cmp, "SINH") == 1)
	return (SINH);
    return (84);
}
