/*
** EPITECH PROJECT, 2019
** options.c
** File description:
** options after identify strs
*/

#include "my.h"

opt_t *attrib_options(opt_t *op, char *options)
{
    for (int i = 0; options[i] != 0; i++) {
        if (options[i] == 'R')
            op->R_o = 1;
        if (options[i] == 'r')
            op->r_o = 1;
        if (options[i] == 't')
            op->t_o = 1;
        if (options[i] == 'd')
            op->d_o = 1;
        if (options[i] == 'l')
            op->l_o = 1;
    }
    return (op);
}

int check_valid_options(char *options)
{
    int valid = 0;

    if (options[0] == 0)
        return (0);
    for (int i = 0; options[i] != 0; i++) {
        valid = 0;
        if (options[i] == 'l' || options[i] == 'R')
            return (1);
        if (options[i] == 'd' || options[i] == 'r')
            return (1);
        if (options[i] == 't')
            return (1);
    }
    return (valid);
}

int options_identify_no_dir(char *str, opt_t *op, int Rstate)
{
    dir_t *main_dir = create_dir(str, op->t_o);

    if (op->r_o == 1)
        main_dir = reverse_all(main_dir);
    if (op->R_o == 0)
        print_dir_t_no(main_dir, op->l_o, op->d_o);
    if (op->R_o == 1)
        print_dir_t(main_dir, op->l_o, op->d_o);
    while (Rstate == 1) {
        if (main_dir->sub == NULL)
            break;
        my_putstr("\n");
        options_identify_no_dir(main_dir->sub->t_name, op, Rstate);
        if (main_dir->sub->next != NULL)
            main_dir->sub = main_dir->sub->next;
        else
            Rstate = 0;
    }
    return (0);
}

int options_identify_dir2(char *str, opt_t *op, int Rstate)
{
    dir_t *main_dir = create_dir(str, op->t_o);

    if (op->r_o == 1)
        main_dir = reverse_all(main_dir);
    print_dir_t(main_dir, op->l_o, op->d_o);
    while (Rstate == 1) {
        if (main_dir->sub == NULL)
            break;
        my_putstr("\n");
        options_identify_dir2(main_dir->sub->t_name, op, Rstate);
        if (main_dir->sub != NULL)
            main_dir->sub = main_dir->sub->next;
        else
            Rstate = 0;
    }
    return (0);
}

int options_identify_dir(opt_t *op, char **str_array)
{
    for (int i = 0; str_array[i] != NULL; i++) {
        options_identify_dir2(str_array[i], op, op->R_o);
        if (str_array[i+1] != NULL)
            my_putstr("\n");
    }
}
