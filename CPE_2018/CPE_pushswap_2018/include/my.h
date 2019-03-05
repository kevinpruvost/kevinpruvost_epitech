/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** Useful to call functions
*/

#ifndef MY_H
#define MY_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct list_t {
    int value;
    int rb;
    struct list_t *previous;
    struct list_t *next;
} list_t;

void my_putchar(char c);
int my_put_nbr(int nb);
int my_atoi(char *);
int my_putstr(char *);
int my_strlen(char *);
float my_getfloat(char *toconvert);
char *my_getnbr(int nbr);
char *my_revstr(char *str);
char *str_add(char *base, char *toadd);
char *load_file_in_mem(char const *filepath);

int print_list(list_t *list);
int swap(list_t **list);
void push(list_t **list_a, list_t **list_b);
int rotate_reverse(list_t **list);
int rotate(list_t **list);
int print_list(list_t *list);

void sa(list_t **list, int *ope);
void sb(list_t **list, int *ope);
void sc(list_t **list_a, list_t **list_b, int *ope);
void pa(list_t **list_a, list_t **list_b, int *ope);
void pb(list_t **list_a, list_t **list_b, int *ope);
void ra(list_t **list, int *ope);
void rb(list_t **list, int *ope);
void rr(list_t **list_a, list_t **list_b, int *ope);
void rra(list_t **list, int *ope);
void rrb(list_t **list, int *ope);
void rrr(list_t **list_a, list_t **list_b, int *ope);

void selection_sorting(list_t **list_a, list_t **list_b, int *ope);

void insertion_sorting(list_t **, list_t **, int *);

void selection_sorting_option(list_t **list_a, list_t **, int *);

void rrb_v(list_t **list, int *ope);
void rra_v(list_t **la, list_t **lb);
void ra_v(list_t **la, list_t **lb);
void rb_v(list_t **list, int *ope);
void rr_v(list_t **list_a, list_t **list_b, int *ope);
void pa_v(list_t **list_a, list_t **list_b, int *ope);
void pb_v(list_t **list_a, list_t **list_b, int *ope);

int second_main(int ac, char **av);
int option_main(int ac, char **av);

list_t *add_list(int value, list_t *list);
list_t *write_in_list(list_t *list_a, char **av, int ac);
void free_list(list_t *list);

int tried(list_t **la, list_t **lb);

#endif
