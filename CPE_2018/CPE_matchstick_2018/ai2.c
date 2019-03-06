/*
** EPITECH PROJECT, 2019
** ai2.c
** File description:
** ai functions
*/

#include "my.h"

match_t *case_1a(match_t *m, int *line_ask, int *matches_ask)
{
    if (m->lines_id_sup5 == 0 && m->lines_id[1] == 1)
        for (int i = 0; i <= m->lines; i++)
            if (m->matches_nb[i] > 1) {
                *line_ask = i;
                *matches_ask = m->matches_nb[i];
            }
    if (m->lines_id[1] == 2) {
        *matches_ask = 1;
        for (int i = 0; i <= m->lines; i++) {
            if (m->matches_nb[i] == 1)
                *line_ask = i;
        }
    }
    return (m);
}

match_t *case_1(match_t *m, int *line_ask, int *matches_ask)
{
    if (m->full_lines == 2 && m->lines_id[1] >= 1) {
        m = case_1a(m, line_ask, matches_ask);
    }
    return (m);
}

match_t *case_2a(match_t *m, int *line_ask, int *matches_ask)
{
    if (m->full_lines == 1 && m->lines_id_sup5 == 1 &&
    m->lines_id[m->max_remove + 1] == 0 &&
    m->lines_id[m->max_remove + 2] == 0) {
        for (int i = 0; i <= m->lines; i++) {
            if (m->matches_nb[i] > 0)
                *line_ask = i;
        }
        if (m->matches_nb[*line_ask] > 2 + (2 * m->max_remove))
            *matches_ask = 1;
        else
            *matches_ask = m->matches_nb[*line_ask] - (2 + m->max_remove);
    }
    return (m);
}

match_t *case_2(match_t *m, int *line_ask, int *matches_ask)
{
    if (m->full_lines == 1 && m->lines_id_sup5 == 0) {
        for (int i = 0; i <= m->lines; i++) {
            if (m->matches_nb[i] > 0)
                *line_ask = i;
        }
        *matches_ask = m->matches_nb[*line_ask] - 1;
    }
    if (m->full_lines == 1 && m->lines_id[1 + m->max_remove] == 1) {
        for (int i = 0; i <= m->lines; i++) {
            if (m->matches_nb[i] > 0)
                *line_ask = i;
        }
        *matches_ask = m->matches_nb[*line_ask] - 1;
    }
    m = case_2a(m, line_ask, matches_ask);
    return (m);
}

match_t *ai_count(match_t *m, int *line_ask, int *matches_ask)
{
    int number = 0;

    m->full_lines = 0;
    m->lines_id_sup5 = 0;
    for (int i = 0; i < m->lines * 2 + 1; i++)
        m->lines_id[i] = 0;
    for (int i = 0; i <= m->lines; i++) {
        if (m->matches_nb[i] > 0) {
            m->full_lines++;
            m->lines_id[m->matches_nb[i]] += 1;
            if (m->matches_nb[i] > m->max_remove)
                m->lines_id_sup5 += 1;
        }
    }
    case_1(m, line_ask, matches_ask);
    case_2(m, line_ask, matches_ask);
    return (m);
}
