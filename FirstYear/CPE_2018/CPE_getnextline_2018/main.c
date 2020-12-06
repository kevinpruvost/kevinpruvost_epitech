/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"
#include "get_next_line.h"
#include <stdio.h>

int main(int ac, char **av)
{
    char *ah;
    int fd = open("test_1",O_RDONLY);

    ah = get_next_line(fd);
    while (ah != NULL) {
        if (ah != NULL)
            printf("ah = |%s|\n",ah);
        else
            printf("ah = (null)\n");
        ah = get_next_line(fd);
    }
    ah = get_next_line(0);
    while (1) {
        if (ah != NULL)
            printf("ah = |%s|\n",ah);
        else
            printf("ah = (null)\n");
        ah = get_next_line(0);
    }
}
