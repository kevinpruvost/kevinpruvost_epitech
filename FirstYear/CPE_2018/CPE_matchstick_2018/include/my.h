/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** my.h
*/

#ifndef MY_H_
#define MY_H_

#include <stdlib.h>
#include <stdio.h>

void my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char *);
int my_strlen(char *);
float my_getfloat(char *toconvert);
int my_getnbr(char *nbr);
char *my_revstr(char *str);
char *str_add(char *base, char *toadd);
char *load_file_in_mem(char const *filepath);
int my_pow(int, int);

typedef struct match_t {
    int lines;
    int length;
    int max_remove;
    char **arr;
    int *matches_nb;
    int max_matches;
    int total_matches;
    int full_lines;
    int *lines_id;
    int lines_id_sup5;
    int *pairs;
    int **pairs_lines;
    int n_lines1;
    int n_linessup1;
} match_t;

match_t *match_malloc(match_t *m);
match_t *count_matches(match_t *m);
void print_game_board(char **);
int line_asking(match_t *);
int matches_asking(match_t *, int *);
void my_putchar(char);
void display_turn_player(int, int);
match_t *case_1(match_t *m, int *line_ask, int *matches_ask);
match_t *case_2(match_t *m, int *line_ask, int *matches_ask);
match_t *pairs_count(match_t *m, int *, int *);
match_t *ai_count(match_t *m, int *line_ask, int *matches_ask);

void ai_processing(match_t *m, int *, int *);

void error_display_matches(int);
void count_remove(match_t *m, int *line_ask, int *matches_ask, int);
match_t *pairs_lines_malloc(match_t *m);
void random_choice(match_t *m, int *line_ask, int *matches_ask);
match_t *array_match(match_t *m, int *line_ask, int *matches_ask);
void free_m(match_t *m);

#endif
