/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Where bsq will work mainly.
*/

#include "../include/my.h"
#include "include/my.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

char *array_to_str(char *str, char **array)
{
    for (int i = 0; array[i] != 0; i++) {
        str = str_add(str, array[i]);
        str = str_add(str, "\n");
    }
    return (str);
}

char *test_cr(char *file)
{
    char **content;
    char *adress = file;
    int nb_cols = 0;
    int nb_rows = 0;

    content = load_2d_arr_from_file(adress);
    for (int i = 0; content[i][0] != 0; i++, nb_rows++);
    for (int i = 0; content[0][i] != 0; i++, nb_cols++);
    content = find_biggest_square(content, nb_rows, nb_cols);

    char *test = malloc(sizeof(char) * 10000);

    test = array_to_str(test, content);
    for (int i = 0; test[i] != 0; i++)
        if (test[i+1] == 0 && test[i] == '\n')
            test[i] = 0;
    free_2d_array(content, nb_rows);
    return (test);
}
