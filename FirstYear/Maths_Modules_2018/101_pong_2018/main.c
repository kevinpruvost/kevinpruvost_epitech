/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main of the 101pong project
*/

#include "include/my.h"

int pong(float x0, float y0, float z0, float x1, float y1, float z1, int n);

int main(int ac, char **av)
{
    if (ac != 8) {
        if (ac == 2)
            if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == 0)
            my_putstr("USAGE\n"
                "\t./101pong x0 y0 z0 x1 y1 z1 n\n\n"
                "DESCRIPTION\n"
                "\tx0   ball abscissa at time t - 1\n"
                "\ty0   ball ordinate at time t - 1\n"
                "\tz0   ball altitude at time t - 1\n"
                "\tx0   ball abscissa at time t\n"
                "\ty0   ball ordinate at time t\n"
                "\tz0   ball altitude at time t\n"
                "\tn    time shift (greater than or equal to zero, integer)\n");
            else
                my_putstr("Please enter the xyz-coordinates of the two vector's extremities and a time shift.\n");
        else
            my_putstr("Please enter the xyz-coordinates of the two vector's \
extremities and a time shift.\n");
        return (84);
    }
    if (my_str_isnum(av[1]) + my_str_isnum(av[2]) + my_str_isnum(av[3]) + my_str_isnum(av[4]) + my_str_isnum(av[5]) + my_str_isnum(av[6]) + my_str_isnum(av[7]) != 7) {
        my_putstr("Please enter only numbers.\n");
        return (84);
	}
    pong(my_getfloat(av[1]), my_getfloat(av[2]), my_getfloat(av[3]), \
         my_getfloat(av[4]), my_getfloat(av[5]), my_getfloat(av[6]), my_getnbr(av[7]));
    return (0);
}
