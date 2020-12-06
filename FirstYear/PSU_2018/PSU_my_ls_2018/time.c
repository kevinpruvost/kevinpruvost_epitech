/*
** EPITECH PROJECT, 2019
** time.c
** File description:
** time
*/

#include "my.h"

char *correct_time(char *time)
{
    int size = my_strlen(time);

    for (int i = 0; i < 10; i++)
        time[size - i] = 0;
    for (int i = 0; i < 4; i++)
        time++;
    return (time);
}
