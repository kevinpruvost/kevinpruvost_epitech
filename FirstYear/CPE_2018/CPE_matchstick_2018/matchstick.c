/*
** EPITECH PROJECT, 2019
** read_player_move_and_print_updated_board_game.c
** File description:
** main funcs of matchstick
*/

#include "get_next_line.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>

match_t *matchstick_play(match_t *m)
{
    int line_ask = 0;
    int matches_ask = 0;

    m = count_matches(m);
    my_putstr("\nYour turn:\n");
    for (; matches_ask == 0 || line_ask == 0;) {
        line_ask = line_asking(m);
        if (line_ask == -1)
            return (NULL);
        matches_ask = matches_asking(m, &line_ask);
    }
    if (matches_ask == -1 || line_ask == -1)
        return (NULL);
    display_turn_player(matches_ask, line_ask);
    m = array_match(m, &line_ask, &matches_ask);
    m = count_matches(m);
    print_game_board(m->arr);
    return (m);
}

match_t *matchstick_ai_play(match_t *m)
{
    int line_ask = 0;
    int matches_ask = 0;
    size_t read = 0;

    m = count_matches(m);
    my_putstr("\nAI's turn...\n");
    ai_processing(m, &line_ask, &matches_ask);
    my_putstr("AI removed ");
    my_put_nbr(matches_ask);
    my_putstr(" match(es) from line ");
    my_put_nbr(line_ask);
    my_putchar('\n');
    for (int i = m->length; i > 0 && matches_ask > 0; i--)
        if (m->arr[line_ask][i] == '|' && matches_ask > 0) {
            m->arr[line_ask][i] = ' ';
            matches_ask--;
        }
    m = count_matches(m);
    print_game_board(m->arr);
    return (m);
}

int matchstick2(int lines, int length, match_t *m)
{
    int win = -1;

    m->length = length;
    m->lines = lines;
    m->matches_nb = malloc(sizeof(int) * (m->lines * 2 + 1));
    m->total_matches = 1;
    print_game_board(m->arr);
    for (; m->total_matches > 0;) {
        m = matchstick_play(m);
        if (m == NULL)
            return (0);
        if (m->total_matches <= 0)
            win = 2;
        else
            m = matchstick_ai_play(m);
        if (m->total_matches <= 0 && win != 2)
            win = 1;
    }
    free_m(m);
    return (win);
}

int matchstick(int lines, int max_remove)
{
    int length = 1 + (2 * lines);
    match_t *m = malloc(sizeof(match_t));
    int n_col = 1;

    m->max_remove = max_remove;
    m->arr = malloc(sizeof(char *) * (lines * 2 + 2));
    m->lines = lines;
    m->length = length;
    for (int i = 0; i < m->lines + 2; i++)
        m->arr[i] = malloc(sizeof(char) * (m->length + 3));
    m = match_malloc(m);
    m->lines_id = malloc(sizeof(int) * (lines * 2 + 2));
    m->pairs = malloc(sizeof(int) * (9));
    m->pairs_lines = malloc(sizeof(int *) * (lines * 2 + 1));
    for (int i = 0; i < lines * 2 + 1; i++)
        m->pairs_lines[i] = malloc(sizeof(int) * (16));
    m->lines_id_sup5 = 0;
    return (matchstick2(lines, length, m));
}

int main(int ac, char **av)
{
    int win;

    if (ac != 3)
        return (84);
    win = matchstick(my_getnbr(av[1]), my_getnbr(av[2]));
    if (win == 1)
        my_putstr("I lost... snif... but I'll get you next time!!\n");
    if (win == 2)
        my_putstr("You lost, too bad...\n");
    return (win);
}
