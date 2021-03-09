/*
** EPITECH PROJECT, 2019
** error_launch_prog.c
** File description:
** error launch_prog
*/

#include "my.h"

int error_launch_prog3(mini_t *w)
{
    args_t *args = w->args;
    int len = 0;

    for (; args != NULL; args = args->next) {
        len = my_strlen(args->args[0]) - 1;
        if (len >= 2 && args->args[0][len] == 'n' &&
            args->args[0][len - 1] == 'a' && args->args[0][len - 2] == 'm') {
            return (84);
        }
    }
    return (0);
}

int error_launch_prog2(mini_t *w)
{
    args_t *args = w->args;
    int error = 0;
    struct stat *statbuff = malloc(sizeof(struct stat));
    int size = 0;

    for (; args != NULL; args = args->next) {
        for (int i = 0; args->args[i] != NULL; i++) {
            (my_strcmp("mysh", args->args[i]) == 1) ? (error = 84) : (0);
            (my_strcmp("./mysh", args->args[i]) == 1) ? (error = 84) : (0);
            (stat(args->args[i], statbuff) != -1)
            ? (size = statbuff->st_size) : (0);
            (size >= 65536) ? (error = 85) : (0);
        }
    }
    if (error == 84)
        my_putstr_error("Binary file (standard input) matches\n");
    if (error == 85 || error == 84)
        return (84);
    return (error_launch_prog3(w));
}

int error_launch_prog(mini_t *w)
{
    seps_t *seps = w->seps;
    int i_nb = 0;
    int p_nb = 1;

    for (int o_nb = 0; seps != NULL; seps = seps->next, p_nb++) {
        (seps->sep[0] == 59) ? (i_nb = 0, o_nb = 0) : (0);
        (seps->sep[0] == '<') ? (i_nb++) : (0);
        (seps->sep[0] == '>') ? (o_nb++) : (0);
        (seps->sep[0] == '|' && i_nb == 0) ? (i_nb++) : (0);
        (seps->sep[0] == '|' && o_nb == 0) ? (o_nb++) : (0);
        (i_nb > 1) ? (my_putstr_error("Ambiguous input redirect.\n")) : (0);
        (o_nb > 1) ? (my_putstr_error("Ambiguous output redirect.\n")) : (0);
        if (o_nb > 1 || i_nb > 1)
            return (84);
        if (p_nb >= 45)
            return (84);
    }
    return (error_launch_prog2(w));
}
