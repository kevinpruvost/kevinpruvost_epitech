/*
** EPITECH PROJECT, 2019
** error_management.c
** File description:
** errors
*/

#include "my.h"

char *str_add_opt(char *s1, char *s2)
{
    s1 = str_add(s1, s2++);
    return (s1);
}

void print_l_error(char *str)
{
    struct stat *statbuf = malloc(sizeof(struct stat));
    char *time = correct_time(ctime(&statbuf->st_mtime));
    int size = my_strlen(my_getnbr(statbuf->st_size));

    stat(str, statbuf);
    print_rights(statbuf);
    print_owners(statbuf, time, size);
    my_putstr(str);
    free(statbuf);
}

int check_str_error(char *str, opt_t *op)
{
    int error = 0;
    struct stat *statbuf = malloc(sizeof(struct stat));

    if (str[0] == '-')
        return (0);
    if (stat(str, statbuf) == -1)
        return (84);
    if (S_ISREG(statbuf->st_mode)) {
        (op->l_o == 1) ? (print_l_error(str)) : (my_putstr(str));
        my_putstr("\n");
        error = 1;
    }
    free(statbuf);
    return (error);
}

int error_management(char **av)
{
    int error = 0;
    opt_t *op = malloc(sizeof(opt_t));
    char *options = malloc(sizeof(char) * 6);
    int n_case = 0;

    options[0] = 0;
    for (int i = 1; av[i] != NULL; i++)
        if (av[i][0] == '-')
            options = str_add_opt(options, av[i]);
    op = attrib_options(op, options);
    for (int i = 1; av[i] != NULL; i++) {
        error = check_str_error(av[i], op);
        if (error == 84)
            exit(84);
        if (error == 1)
            n_case++;
    }
    free(op);
    return (n_case);
}
