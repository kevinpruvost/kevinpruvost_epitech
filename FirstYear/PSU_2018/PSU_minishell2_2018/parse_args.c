/*
** EPITECH PROJECT, 2019
** parse_args.c
** File description:
** parse_args
*/

#include "my.h"

char **create_args_for_parse(char *str)
{
    char **args;
    int nb_words = 1;

    for (int i = 0; str[i] != 0; i++)
        if (str[i] == ' ' || str[i] == '\t')
            nb_words++;
    args = malloc(sizeof(char *) * (nb_words + 1));
    for (int i = 0; i < nb_words; i++) {
        args[i] = malloc(sizeof(char) *
        (my_strlen("/usr/bin/") * my_strlen(str) + 1));
        for (int j = 0; j <= my_strlen("/usr/bin/") * my_strlen(str); j++)
            args[i][j] = 0;
        args[i+1] = NULL;
    }
    return (args);
}

int is_sep(char *str, int i)
{
    char check[5];

    check[0] = 59;
    check[1] = '|';
    check[2] = '<';
    check[3] = '>';
    if ((str[i] == '>' && str[i+1] == '>') ||
        (str[i] == '<' && str[i+1] == '<'))
        return (2);
    for (int j = 0; j < 4; j++)
        if (str[i] == check[j])
            return (1);
    return (0);
}

void parse_args_actions(mini_t *w, char **args, char *test, int nb)
{
    if (nb == 1) {
        add_args(w, args);
        clean_array(args);
    }
    if (nb == 2) {
        append(args, test);
        clean_str(test);
    }
}

void free_parse_args(char *test, char **args, char *str)
{
    int nb_words = 1;

    free(test);
    for (int i = 0; str[i] != 0; i++)
        if (str[i] == ' ' || str[i] == '\t')
            nb_words++;
    for (int i = 0; i < nb_words; i++)
        free(args[i]);
    free(args);
}

void parse_args(mini_t *w, char *str, int qu)
{
    char *test = create_test_parse(my_strlen(str));
    char **args = create_args_for_parse(str);

    for (int i = 0, j = 0; str[i] != 0; i++) {
        (str[i+1] == 0 && str[i] > 32 && str[i] != '"' && is_sep(str, i) == 0)
        ? (test[j] = str[i], qu = -1) : (0);
        (str[i+1] == 0 && str[i] == '"') ? (test[j] = '"', qu = -1) : (0);
        if (((str[i] == ' ' || str[i+1] == 0) && qu == -1)) {
            j = 0;
            parse_args_actions(w, args, test, 2);
        }
        if (is_sep(str, i) > 0 || str[i+1] == 0) {
            i += is_sep(str, i);
            parse_args_actions(w, args, test, 1);
        }
        (str[i] == '"') ? (qu *= -1) : (0);
        (i > my_strlen(str)) ? (i = my_strlen(str)) : (0);
        (str[i] != ' ' && str[i] != '"') ? (test[j] = str[i], j++) : (0);
    }
    free_parse_args(test, args, str);
}
