/*
** EPITECH PROJECT, 2019
** str_to_word_array.c
** File description:
** str to array
*/

#include "my.h"

void count(int *n_words, char *str)
{
    for (int i = 0; str[i] != 0; i++)
        if (str[i] == ' ') {
            *n_words += 1;
            i++;
        }
}

char **malloc_str_to_word_array(char *str, int n_words, char **array)
{
    array = malloc(sizeof(char *) * (n_words + 1));
    for (int i = 0; i < n_words; i++) {
        array[i] = malloc(sizeof(char) * (my_strlen(str) + 1));
        array[i+1] = NULL;
    }
    return (array);
}

char **str_to_word_array(char *str)
{
    char **array;
    int n_words = 1;
    int p = 0;
    int gmode = -1;

    if (str == NULL)
        return (NULL);
    count(&n_words, str);
    array = malloc_str_to_word_array(str, n_words, array);
    for (int i = 0, x = 0; str[i] != 0; i++, x++) {
        (str[i] == '"' || str[i] == 39) ? (gmode *= (-1), i++) : (0);
        if (str[i] != ' ' && str[i] != 0 || gmode == 1) {
            array[p][x] = str[i];
            array[p][x+1] = '\0';
        } else
            p++, x = -1;
        (str[i] == 0) ? (p--) : (0);
    }
    array[p+1] = NULL;
    return (array);
}
