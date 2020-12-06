/*
** EPITECH PROJECT, 2018
** main_2.c
** File description:
** main2
*/

#include "include/my.h"
#include <curses.h>

char **malloc_array(char *content, char **array)
{
    int lines = 1;
    int line_size = 0;

    for (int i = 0; content[i] != 0; i++)
        if (content[i] == '\n')
            lines++;
    array = malloc(sizeof(char *) * lines + 1);
    for (int i = 0, j = 0; content[i] != 0; i++) {
        if (content[i] != '\n')
            line_size++;
        else {
            array[j] = malloc(sizeof(char) * (line_size + 5));
            line_size = 0, j++;
        }
        if (content[i+1] == 0)
            array[j] = malloc(sizeof(char) * (line_size + 5));
    }
    array[lines] = malloc(sizeof(char));
    array[lines] = 0;
    return (array);
}

void free_array(char **array)
{
    int i = 0;

    for (i = 0; array[i+1] != 0; i++);
    for (; i >= 0; i--)
        free(array[i]);
    free(array);
}

char **str_to_array_sokoban(char *content)
{
    int largeur_max = 0;
    int longueur_max = 0;
    char **array = malloc_array(content, array);

    for (int i = 0, j = 0, k = 0; content[i] != 0; i++) {
        array[j][k] = content[i];
        k++;
        if (content[i] == '\n' && content[i+1] != 0) {
            array[j][k] = 0;
            j++;
            k = 0;
        }
    }
    return (array);
}

int my_sokoban(char *file)
{
    char *content = load_file_in_mem(file);
    char **array = str_to_array_sokoban(content);
    char **arrayBase = str_to_array_sokoban(content);
    int win = 0;
    int error = error_managing(array);

    if (error == 84) {
        free_array(array);
        free_array(arrayBase);
        return (84);
    }
    win = my_sokoban_processes(array, arrayBase);
    free_array(array);
    free_array(arrayBase);
    return (win);
}
