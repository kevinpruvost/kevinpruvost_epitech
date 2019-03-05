/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

int help_message(void)
{
    char *message = "USAGE\n"
        "    ./105torus opt a0 a1 a2 a3 a4 n\n"
        "\n"
        "DESCRIPTION\n"
        "    opt       method option:\n"
        "                  1 for the bisection method\n"
        "                  2 for Newton's method\n"
        "                  3 for the secant method\n"
        "    a[0-4]    coefficients of the equation\n"
        "    n         precision (the application of the polynomial to the solution should\n"
        "              be smaller than 10^-n)\n";

    my_putstr(message);
}

int error_check(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
        } else if (str[i] == '.' || str[i] == ',' || str[i] == '+' || str[i] == '-') {
        } else
            return (84);
    }
    return (0);
}

int error_management(char **av)
{
    for (int i = 1; av[i] != NULL; i++) {
        if (error_check(av[i]) == 84)
            exit(84);
    }
    if (av[1][0] >= '0' && av[1][0] <= '3')
        torus(av);
    else
        exit(84);
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 2) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == 0) {
            help_message();
            return (0);
        }
        return (84);
    } else if (ac != 8) {
        return (84);
    } else
        error_management(av);
    return (0);
}
