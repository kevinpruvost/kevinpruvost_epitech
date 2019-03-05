/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Where bsq will work mainly.
*/

#include "include/my.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    char **content;
    char *adress = av[1];
    int nb_cols = 0;
    int nb_rows = 0;

    content = load_2d_arr_from_file(adress);
    for (int i = 0; content[i][0] != 0; i++, nb_rows++);
    for (int i = 0; content[0][i] != 0; i++, nb_cols++);
    content = find_biggest_square(content, nb_rows, nb_cols);
    for (int i = 0; content[i][0] != 0; i++) {
        my_putstr(content[i]);
        my_putchar('\n');
    }
    free_2d_array(content, nb_rows);
    return (0);
}
