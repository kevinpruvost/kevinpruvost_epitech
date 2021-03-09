/*
** EPITECH PROJECT, 2019
** spec_char.c
** File description:
** special characters
*/

#include "my.h"

int identify_spec_char(char *buffer, char *new_str, int pos)
{
    for (int i = 0; buffer[i] != 0; i++) {
        (buffer[i] == '\\') ? (replace_buffer_char(buffer, i)) : (0);
    }
    for (int i = 0; buffer[i] != 0; i++)
        new_str[pos + i] = buffer[i];
}

void rewrite_new_str(char *new_str, char *str, char **specs)
{
    int quote_mode = -1;
    int spec = 0;

    for (int i = 0, j = 0; str[i] != 0; i++) {
        (str[i] == 39) ? (quote_mode *= -1) : (0);
        if (quote_mode == -1 && str[i] != 39) {
            new_str[j] = str[i];
            j++;
        }
        if (quote_mode == 1 && str[i] == 39) {
            for (int k = 0; specs[spec][k] != 0; k++)
                new_str[j] = specs[spec][k], j++;
            spec++;
        }
    }
    for (int i = 0; new_str[i] != 0; i++) {
        str[i] = new_str[i];
        str[i+1] = 0;
    }
}

int identify_spec_chars(char *buffer, char *new_str, char *str, char **specs)
{
    int quote_mode = -1;
    int error = 0;
    int spec = 0;
    int pos = 0;

    for (int i = 0, j = 0; str[i] != 0; i++) {
        (str[i] == 39) ? (quote_mode *= -1) : (0);
        if (quote_mode == 1) {
            (str[i] == 39) ?
            (pos = i) : (buffer[j] = str[i], j++);
        }
        if (str[i] == 39 && quote_mode == -1) {
            identify_spec_char(buffer, new_str, pos);
            free(specs[spec]);
            specs[spec] = my_strcpy(buffer);
            clean_str(buffer), j = 0, spec++;
        }
        (str[i+1] == 0 && quote_mode == 1) ? (error = 1) : (0);
    }
    return (error);
}

int check_spec_char(char *str)
{
    char *buffer = create_string(10);
    char *new_str = create_string(my_strlen(str));
    char **specs = create_char_array(my_strlen(str), my_strlen(str));
    int error = 0;

    error = identify_spec_chars(buffer, new_str, str, specs);
    rewrite_new_str(new_str, str, specs);
    free(buffer);
    return (error);
}
