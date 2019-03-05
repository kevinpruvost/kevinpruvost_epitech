/*
** EPITECH PROJECT, 2019
** help_option.c
** File description:
** help option
*/

#include "my.h"

void help_option(void)
{
    my_putstr("My_ls\n\n");
    my_putstr("USAGE\n\n");
    my_putstr("    ./my_ls     (current directory)\n        OR");
    my_putstr("\n    ./my_ls files_names\n");
    my_putstr("OR\n");
    my_putstr("    ./my_ls options files_names\n");
    my_putstr("        options: '-?' format, \n");
    my_putstr("               -l : long display format\n");
    my_putstr("               -R : recursive, display all sub-directories\n");
    my_putstr("               -r : reverse sort order\n");
    my_putstr("               -t : sort by modification date\n");
    my_putstr("               -d : display only directories\n\n");
    my_putstr("        files_names:\n");
    my_putstr("               files names and directories names\n");
}
