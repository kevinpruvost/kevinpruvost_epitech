/*
** EPITECH PROJECT, 2019
** ai.c
** File description:
** artificial intelligence creation
*/

#include "my.h"
#include <stdlib.h>
#include <stdio.h>

match_t *pairs_count(match_t *m, int *line_ask, int *matches_ask)
{
    for (int i = 0; i <= m->lines; i++) {
        for (int j = 0; j <= 8; j++)
            m->pairs_lines[i][j] = 0;
    }
    for (int i = 8; i >= 0; i--)
        m->pairs[i] = 0;
    for (int i = 0, count = 0; i <= m->lines; i++) {
        count = m->matches_nb[i];
        for (int j = 8; j >= 0 && count > 0; j--) {
            if (count >= my_pow(2, j)) {
                count -= my_pow(2, j);
                m->pairs[j] += 1;
                m->pairs_lines[i][j] += 1;
            }
        }
    }
    return (m);
}

match_t *final_count(match_t *m)
{
    m->n_lines1 = 0;
    m->n_linessup1 = 0;
    for (int i = 0; i <= m->lines; i++) {
        if (m->matches_nb[i] == 1)
            m->n_lines1 += 1;
        if (m->matches_nb[i] > 1)
            m->n_linessup1 += 1;
    }
    return (m);
}

void theorem_choice(match_t *m, int *line_ask, int *matches_ask)
{
    int remove = 0;
    int remove_big = 0;

    for (int i = 8; i >= 0; i--) {
        if (m->pairs[i] % 2 == 1)
            remove += my_pow(2, i);
        if (m->pairs[i] % 2 == 1 && remove_big == 0)
            remove_big += my_pow(2, i);
    }
    *line_ask = 1;
    count_remove(m, line_ask, matches_ask, remove);
}

void final_choice(match_t *m, int *line_ask, int *matches_ask)
{
    int reste = 0;

    if (m->n_lines1 % 2 == 0)
        reste = 1;
    for (int i = 0; i <= m->lines && *line_ask == 0; i++)
        if (m->matches_nb[i] > 1)
            *line_ask = i;
    if (m->matches_nb[*line_ask] > m->max_remove)
        *matches_ask = m->matches_nb[*line_ask] - m->max_remove - reste;
    else
        *matches_ask = m->matches_nb[*line_ask] - reste;
}

void ai_processing(match_t *m, int *line_ask, int *matches_ask)
{
    m = count_matches(m);
    m = pairs_count(m, line_ask, matches_ask);
    m = final_count(m);
    if (m->n_linessup1 > 1)
        theorem_choice(m, line_ask, matches_ask);
    else if (m->n_linessup1 == 1)
        final_choice(m, line_ask, matches_ask);
    else
        random_choice(m, line_ask, matches_ask);
    if (*line_ask == 0 || *matches_ask == 0) {
        random_choice(m, line_ask, matches_ask);
        if (m->matches_nb[*line_ask] >= 3 && m->matches_nb[*line_ask]
            <= 2 + m->max_remove)
            *matches_ask = m->matches_nb[*line_ask] - 2;
        else if (m->matches_nb[*line_ask] > 2 + m->max_remove &&
            m->matches_nb[*line_ask] <= 2 + (2 * m->max_remove))
            *matches_ask = m->matches_nb[*line_ask] - (2 + m->max_remove);
        else
            *matches_ask = 1;
    }
}
