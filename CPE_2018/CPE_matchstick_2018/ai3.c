/*
** EPITECH PROJECT, 2019
** ai3.c
** File description:
** ai functions
*/

#include "my.h"

match_t *pairs_lines_malloc(match_t *m)
{
    if (m->pairs_lines == NULL)
        m->pairs_lines = malloc(sizeof(int *) * m->lines * 2);
    if (m->pairs_lines[0] == NULL)
        for (int i = 0; i <= m->lines * 2; i++)
            m->pairs_lines[i] = malloc(sizeof(int) * 9);
    return (m);
}

int *count_binary_line(int line)
{
    int *count_binary = malloc(sizeof(int) * 9);

    for (int i = 8; i >= 0; i--)
        count_binary[i] = 0;
    for (int i = 8; i >= 0; i--) {
        if (line >= my_pow(2, i)) {
            line -= my_pow(2, i);
            count_binary[i] += 1;
        }
    }
    return (count_binary);
}

int *count_binary_test(int line, int *count_binary)
{
    for (int i = 8; i >= 0; i--) {
        count_binary[i] = 0;
    }
    for (int i = 8; i >= 0 && line != 0; i--)
        if (line >= my_pow(2, i)) {
            line -= my_pow(2, i);
            count_binary[i] += 1;
        }
    return (count_binary);
}

int verify(int *test, int *remove_binary, int *count_binary)
{
    for (int i = 8; i >= 0; i--) {
        if (remove_binary[i] == 0) {
            if (test[i] != count_binary[i])
                return (0);
        } else {
            if (test[i] == count_binary[i])
                return (0);
        }
    }
    return (1);
}

void count_remove(match_t *m, int *line_ask, int *matches_ask, int remove)
{
    int *count_binary = m->pairs_lines[*line_ask];
    int *remove_binary = count_binary_line(remove);
    int count = 0;
    int *test = malloc(sizeof(int) * 9);

    for (int i = 1; i <= m->max_remove && count == 0
    && i <= m->matches_nb[*line_ask]; i++) {
        test = count_binary_test(m->matches_nb[*line_ask] - i, test);
        if (verify(test, remove_binary, count_binary) == 1)
            count = i;
    }
    if (count == 0 && *line_ask < m->lines) {
        *line_ask += 1;
        count_remove(m, line_ask, matches_ask, remove);
    } else
        *matches_ask = count;
}
