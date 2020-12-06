/*
** EPITECH PROJECT, 2019
** manage_arg.c
** File description:
** manage arc
*/

#include "my.h"

void manage_arg(char *options, opt_t *op, char **str_array)
{
    if ((options[0] == 0 || check_valid_options(options) == 0)
    && my_arraylen(str_array) <= 1) {
        if (my_arraylen(str_array) == 1)
            info_dir_no_option(str_array[0]);
        else
            info_dir_no_option(".");
    } else if (str_array == NULL && check_valid_options(options) == 1)
        options_identify_no_dir(".", op, op->R_o);
    if (check_valid_options(options) == 1)
        options_identify_dir(op, str_array);
}
