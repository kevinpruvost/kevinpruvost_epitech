/*
** EPITECH PROJECT, 2019
** match_utilities.c
** File description:
** matching game utilities
*/

#include "my.h"

match_t *match_malloc2(match_t *m, int i, int n_col)
{
    if (i == 0 || i == m->lines + 1) {
        for (int j = 0; j < m->length; j++) {
            m->arr[i][j] = '*';
            m->arr[i][j+1] = 0;
        }
    } else {
        m->arr[i][0] = '*';
        for (n_col = 1; n_col < (m->lines * 2); n_col++) {
            if (n_col < (m->length / 2) - (i - 1))
                m->arr[i][n_col] = ' ';
            else if (n_col > (m->length / 2) + (i - 1))
                m->arr[i][n_col] = ' ';
            else
                m->arr[i][n_col] = '|';
        }
        m->arr[i][m->length-1] = '*';
        m->arr[i][m->length] = 0;
    }
    return (m);
}

match_t *match_malloc(match_t *m)
{
    for (int i = 0, n_col = 1; i < m->lines + 2; i++) {
        m = match_malloc2(m, i, n_col);
    }
    m->arr[m->lines + 2] = NULL;
    return (m);
}

match_t *count_matches(match_t *m)
{
    int number = 0;

    m->max_matches = 0;
    m->total_matches = 0;
    for (int i = 0; i <= m->lines; i++) {
        number = 0;
        for (int j = 0; m->arr[i][j] != 0; j++) {
            if (m->arr[i][j] == '|')
                number++;
        }
        m->matches_nb[i] = number;
        if (m->max_matches < number)
            m->max_matches = number;
        m->total_matches += number;
    }
    return (m);
}
