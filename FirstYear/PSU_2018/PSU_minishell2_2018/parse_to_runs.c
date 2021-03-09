/*
** EPITECH PROJECT, 2019
** parse_to_runs.c
** File description:
** parse to runs
*/

#include "my.h"

char *create_test_parse(int i)
{
    char *test = malloc(sizeof(char) * (i + 1));

    for (int j = 0; j <= i; j++)
        test[j] = 0;
    return (test);
}

void parse_to_runs(mini_t *w, char *str)
{
    char *test = create_test_parse(my_strlen(str));
    int quote = -1;
    int sep = 0;

    for (int i = 0, j = 0; str[i] != 0; i++) {
        (str[i+1] == 0 && str[i] > 32 && str[i] != '"' && is_sep(str, i) == 0)
            ? (test[j] = str[i], quote = -1) : (0);
        if ((((str[i] == ' ' || str[i+1] == 0) && quote == -1) ||
            (str[i] == '"' && quote == 1)) && sep == 0) {
            j = 0;
            add_to_runs(w, test);
            clean_str(test), sep = 1;
        }
        (is_sep(str, i) > 0) ? (i += is_sep(str, i), sep = 0) : (0);
        (i > my_strlen(str)) ? (i = my_strlen(str)) : (0);
        (str[i] == '"') ? (quote *= -1) : (0);
        (j == 0) ? (clean_str(test)) : (0);
        (str[i] > 32 && sep == 0) ? (test[j] = str[i], j++) : (0);
    }
}
