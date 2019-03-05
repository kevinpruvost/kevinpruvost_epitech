/*
** EPITECH PROJECT, 2018
** find_bsq.c
** File description:
** Where bsq will work mainly.
*/

#include "include/coordinates.h"
#include "include/my.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int is_square(char **map, coord *data, int square_size, int *id_data)
{
    int back = 0;

    if (*id_data < square_size)
        return (0);
    for (int i = data->j; i != data->j + square_size && back == 0; i++) {
        for (int j = data->i; j != data->i + square_size && back == 0; j++) {
            if (map[i][j] == 'o' || map[i][j] == 0) {
                *id_data = j - data->i;
                if ((i - data->j) > (j - data->i))
                    *id_data = i - data->j;
                back = 1;
            }
        }
    }
    if (back == 1)
        return (0);
    return (1);
}

int **id_malloc(int nb_rows, int nb_cols, int big_limit)
{
    int **id_data = 0;
    int j = 0;
    int i = 0;

    id_data = malloc(sizeof(int *) * (nb_cols));
    for (i = 0; i < nb_cols; i++) {
        id_data[i] = malloc(sizeof(int) * (nb_rows));
        for (j = 0; j < nb_rows; j++) {
            id_data[i][j] = big_limit;
        }
    }
    id_data[i] = malloc(sizeof(int));
    return (id_data);
}

int check_biggest_int(int **id_data, int big_limit, int nb_rows, int nb_cols)
{
    int biggest_int = 0;
    int j = 0;

    for (int i = 0; i < nb_rows; i++) {
        for (j = 0; j < nb_cols; j++) {
            if (id_data[i][j] > biggest_int) {
                biggest_int = id_data[i][j];
            }
        }
    }
    if (biggest_int >= big_limit)
        biggest_int = big_limit;
    return (biggest_int);
}

char **find_biggest_square(char **map, int nb_rows, int nb_cols)
{
    int limit = nb_rows;
    int found = 0;
    coord *data = malloc(sizeof(data));
    int **id_data = id_malloc(nb_rows, nb_cols, limit);

    for (; limit > 0 && found == 0; limit--) {
        limit = check_biggest_int(id_data, limit, nb_cols, nb_rows);
        for (data->j = 0; data->j <= nb_rows - 1 && found == 0; data->j++) {
            for (data->i = 0; data->i <= nb_cols - 1 && found == 0; data->i++) {
                found = is_square(map, data, limit, &id_data[data->i][data->j]);
            }
        }
    }
    data->i--;
    data->j--;
    limit++;
    if (found == 1)
        map = rewrite_map(map, data->i, data->j, limit);
    free_id_data(id_data, nb_cols);
    free(data);
    return (map);
}

void free_id_data(int **id_data, int nb_cols)
{
    int j = 0;
    int i = 0;

    for (i = 0; i < nb_cols; i++);
    for (; i > 0; i--) {
        free(id_data[i]);
    }
    free(id_data);
}
