/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main funcs
*/

#include "my.h"

int info_dir_no_option(char *dir_name)
{
    int fd = 0;
    DIR *pointer;
    struct dirent *dirp;
    dir_t *main_dir = create_dir(dir_name, 0);

    if (dir_name == NULL)
        return (84);
    print_dir_t_no(main_dir, 0, 0);

    return (0);
}

char **case_alone(char **str_array)
{
    str_array = malloc(sizeof(char *) * 2);

    str_array[0] = malloc(sizeof(char) * 5);
    str_array[0][0] = '.';
    str_array[0][1] = 0;
    str_array[1] = NULL;
    return (str_array);
}

opt_t *create_op(void)
{
    opt_t *op = malloc(sizeof(opt_t));

    op->R_o = 0;
    op->r_o = 0;
    op->d_o = 0;
    op->t_o = 0;
    op->l_o = 0;
    return (op);
}

int info_identify(char **av, int n_case)
{
    char *options = options_create();
    char **str_array = NULL;
    opt_t *op = create_op();

    for (int i = 1; av[i] != NULL; i++) {
        if (av[i][0] == '-')
            av[i]++, options = str_add(options, av[i]);
        else if (av[i][0] == 10)
            n_case++;
        else {
            if (av[i][my_strlen(av[i]) - 1] == '/')
                av[i][my_strlen(av[i]) - 1] = 0;
            str_array = str_add_to_array(av[i], str_array);
        }
    }
    (str_array == NULL) ? (str_array = case_alone(str_array)) : (0);
    if (n_case == my_arraylen(str_array))
        return (0);
    op = attrib_options(op, options);
    manage_arg(options, op, str_array);
}

int main(int ac, char **av)
{
    int n_case;

    if (ac == 2) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == 0) {
            help_option();
            return (0);
        }
    }
    if (ac >= 2) {
        n_case = error_management(av);
        info_identify(av, n_case);
    } else
        info_dir_no_option(".");
    return (0);
}
