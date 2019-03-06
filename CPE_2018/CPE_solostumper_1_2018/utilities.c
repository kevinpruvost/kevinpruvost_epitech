/*
** EPITECH PROJECT, 2019
** utilities.c
** File description:
** functions to use in count words
*/

#include "my.h"
#include <stdlib.h>
#include <stdio.h>

int my_strlen(char *str)
{
    int i = 0;

    for (; str[i] != 0; i++);
    return (i);
}

int compare_str(char *str1, char *str2)
{
    int result = 1;

    if (str1 == NULL || str2 == NULL)
        return (0);
    if (my_strlen(str1) != my_strlen(str2))
        return (0);
    for (int i = 0; str1[i] != 0; i++)
        if (str1[i] != str2[i])
            result = 0;
    return (result);
}

int *already_compare2(char **words, int words_number, int *already, int j)
{
    for (int i = 0; i < words_number; i++) {
        if (compare_str(words[i], words[j]) == 1 && i != j
            && already[i] == 0 && already[j] == 0) {
            already[i] = 1;
        }
    }
    return (already);
}

int *already_compare(char **words, int words_number, int *occ)
{
    int *already = malloc(sizeof(int) * (words_number + 1));

    for (int i = 0; i < words_number; i++)
        already[i] = 0;
    for (int i = 0; i < words_number; i++)
        already = already_compare2(words, words_number, already, i);
    return (already);
}

void display_words(int words_number, char **words, int *occ)
{
    int *already = already_compare(words, words_number, occ);

    for (int i = 0; i < words_number; i++)
        if (already[i] == 0 && words[i][0] != 0)
            printf("%s: %d\n", words[i], occ[i]);
}
