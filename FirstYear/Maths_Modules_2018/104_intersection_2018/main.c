/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main func of 104intersection
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

void intersection(char **av)
{
    int mode = my_atoi(av[1]);

    if (mode == 1)
        sphere(av);
    if (mode == 2)
        cylinder(av);
    if (mode == 3)
        cone(av);
}

int main(int ac, char **av)
{
    if (ac == 9) {
        intersection(av);
    } else if (ac == 2) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
            printf("USAGE\n    ./104intersection opt xp yp zp xv yv zv p\n\n"
                "DESCRIPTION\n"
                "    opt\t\t    surface option: 1 for a sphere, 2 for a cylinder, 3 for a cone\n"
                "    (xp, yp, zp)    coordinates of a point by which the light ray passes through\n"
                "    (xv, yv, zv)    coordinates of a vector parallel to the light ray\n"
                "    p\t\t    parameter: radius of the sphere, radius of the cylinder, or\n"
                "\t\t    angle formed by the cone and the Z-axis\n");
        } else
            return (84);
    } else {
        return (84);
    }
    return (0);
}
