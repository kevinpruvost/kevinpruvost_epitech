/*
** EPITECH PROJECT, 2019
** interaction.c
** File description:
** interaction with user
*/

#include "my.h"
#include "get_next_line.h"

int line_asking(match_t *m)
{
    int line_ask = 0;
    char *line;

    for (; line_ask <= 0 || line_ask > m->lines
    || m->matches_nb[line_ask] <= 0;) {
        my_putstr("Line: ");
        line = get_next_line(0);
        if (line == NULL)
            return (-1);
        line_ask = my_getnbr(line);
        if (line_ask <= 0 || line_ask > m->lines
        || m->matches_nb[line_ask] <= 0) {
            my_putstr("Error: this line is out of range\n");
        }
    }
    free(line);
    return (line_ask);
}

int matches_asking(match_t *m, int *line_ask)
{
    int matches_ask = 0;
    char *line;

    my_putstr("Matches: ");
    line = get_next_line(0);
    if (line == NULL)
        return (-1);
    matches_ask = my_getnbr(line);
    if (matches_ask <= 0)
        my_putstr("Error: you have to remove at least one match\n");
    if (matches_ask > m->matches_nb[*line_ask]) {
        my_putstr("Error: not enough matches on this line\n");
        matches_ask = 0;
    }
    if (matches_ask > m->max_remove) {
        error_display_matches(m->max_remove);
        matches_ask = 0;
    }
    free(line);
    return (matches_ask);
}

match_t *array_match(match_t *m, int *line_ask, int *matches_ask)
{
    for (int i = m->length; i > 0 && *matches_ask > 0; i--)
        if (m->arr[*line_ask][i] == '|' && *matches_ask > 0) {
            m->arr[*line_ask][i] = ' ';
            *matches_ask -= 1;
        }
    return (m);
}
