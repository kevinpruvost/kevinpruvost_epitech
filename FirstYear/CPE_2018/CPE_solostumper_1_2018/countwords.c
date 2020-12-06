/*
** EPITECH PROJECT, 2019
** countwords.c
** File description:
** function that count words and display their numbers
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

char **malloc_array2(char **words, int n, int words_number, char *string)
{
    n = 0;
    for (int i = 0, j = 0; string[j] != 0; j++, n++) {
        if (string[j] == '\n' || string[j] == ' ' || string[j] == '\t') {
            words[i][n] = 0, n = 0, i++, j++;
            words[i] = malloc(sizeof(char) * my_strlen(string));
            if (words[i] == NULL)
                return (NULL);
        }
        while ((string[j] == '\n' || string[j] == ' ' || string[j] == '\t')
               && string[j+1] != 0)
            j++;
        if (string[j] != 0)
            words[i][n] = string[j];
    }
    words[words_number] = NULL;
    return (words);
}

char **malloc_array(char *string)
{
    char **words;
    int n = 0;
    int words_number = 1;

    for (int i = 0; string[i] != 0; i++)
        if (string[i] == ' ' || string[i] == '\t' || string[i] == '\n')
            words_number++;
    words = malloc(sizeof(char *) * (words_number + 1));
    words[0] = malloc(sizeof(char) * my_strlen(string));
    if (words == NULL || words[0] == NULL)
        return (NULL);
    words = malloc_array2(words, n, words_number, string);
    return (words);
}

int *compare_strings(char **words, int words_number, int *occ, int j)
{
    for (int i = 0; i < words_number; i++)
        if (compare_str(words[i], words[j]) == 1 && i != j) {
            occ[i] += 1;
        }
    return (occ);
}

int countwords(char *string)
{
    char **words = malloc_array(string);
    int words_number = 1;
    int *occ;

    if (error_management(string) <= 0) {
        printf("\n");
        return (0);
    }
    if (words == NULL)
        return (84);
    for (; words[words_number] != NULL; words_number++);
    occ = malloc(sizeof(int) * (words_number + 1));
    for (int i = 0; i < words_number; i++)
        occ[i] = 1;
    if (occ == NULL)
        return (84);
    for (int i = 0; i < words_number; i++)
        occ = compare_strings(words, words_number, occ, i);
    display_words(words_number, words, occ);
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        printf("\n");
    else {
        if (countwords(av[1]) == 84)
            return (84);
    }
    return (0);
}
