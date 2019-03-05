/*
** EPITECH PROJECT, 2019
** calculs.c
** File description:
** calculs
*/

#include "my.h"
#include <stdio.h>
#include <math.h>

void sphere(char **av)
{
    float nb_inter = 0;
    float xp = my_getfloat(av[2]);
    float yp = my_getfloat(av[3]);
    float zp = my_getfloat(av[4]);
    float xv = my_getfloat(av[5]);
    float yv = my_getfloat(av[6]);
    float zv = my_getfloat(av[7]);
    float parameter = my_getfloat(av[8]);

    printf("Sphere of radius %d\n", (int)(parameter));
    printf("Line passing through the point (%d, %d, %d) and parallel to the vector (%d, %d, %d)\n",
           (int)(xp), (int)(yp), (int)(zp), (int)(xv), (int)(yv), (int)(zv));

    float a = powf(xv, 2) + powf(yv, 2) + powf(zv, 2);
    float b = 2 * ((xp * xv) + (yp * yv) + (zp * zv));
    float c = powf(xp, 2) + powf(yp, 2) + powf(zp, 2) - powf(parameter, 2);

    float del = delta(a, b, c);

    if (del < 0)
        printf("No intersection point.\n");
    if (del == 0) {
        float sol = (-b) / (2 * a);
        printf("1 intersection point:\n");
        printf("(%.3f, %.3f, %.3f)\n", (sol * xv) + xp, (sol * yv) + yp, (sol * zv) + zp);
    }
    if (del > 0) {
        float sol1 = (-b + sqrtf(del)) / (2 * a);
        float sol2 = (-b - sqrtf(del)) / (2 * a);
        printf("2 intersection points:\n");
        printf("(%.3f, %.3f, %.3f)\n", (sol1 * xv) + xp, (sol1 * yv) + yp, (sol1 * zv) + zp);
	printf("(%.3f, %.3f, %.3f)\n", (sol2 * xv) + xp, (sol2 * yv) + yp, (sol2 * zv) + zp);
    }
    
}

void cylinder(char **av)
{
    float nb_inter = 0;
    float xp = my_getfloat(av[2]);
    float yp = my_getfloat(av[3]);
    float zp = my_getfloat(av[4]);
    float xv = my_getfloat(av[5]);
    float yv = my_getfloat(av[6]);
    float zv = my_getfloat(av[7]);
    float parameter = my_getfloat(av[8]);

    printf("Cylinder of radius %d\n", (int)(parameter));
    printf("Line passing through the point (%d, %d, %d) and parallel to the vector (%d, %d, %d)\n",
           (int)(xp), (int)(yp), (int)(zp), (int)(xv), (int)(yv), (int)(zv));

    float a = powf(xv, 2) + powf(yv, 2);
    float b = 2 * ((xp * xv) + (yp * yv));
    float c = powf(xp, 2) + powf(yp, 2) - powf(parameter, 2);

    float del = delta(a, b, c);
    
    if (del < 0)
        printf("No intersection point.\n");
    if (del == 0) {
        if (xv == 0 && yv == 0) {
            printf("There is an infinite number of intersection points.\n");
        } else {
            float sol = (-b) / (2 * a);
            printf("1 intersection point:\n");
            printf("(%.3f, %.3f, %.3f)\n", (sol * xv) + xp, (sol * yv) + yp, (sol * zv) + zp);
        }
    }
    if (del > 0) {
        float sol1 = (-b + sqrtf(del)) / (2 * a);
        float sol2 = (-b - sqrtf(del)) / (2 * a);
	printf("2 intersection points:\n");
	printf("(%.3f, %.3f, %.3f)\n", (sol1 * xv) + xp, (sol1 * yv) + yp, (sol1 * zv) + zp);
	printf("(%.3f, %.3f, %.3f)\n", (sol2 * xv) + xp, (sol2 * yv) + yp, (sol2 * zv) + zp);
    }

}

void cone(char **av)
{
    float nb_inter = 0;
    float xp = my_getfloat(av[2]);
    float yp = my_getfloat(av[3]);
    float zp = my_getfloat(av[4]);
    float xv = my_getfloat(av[5]);
    float yv = my_getfloat(av[6]);
    float zv = my_getfloat(av[7]);
    float parameter = my_getfloat(av[8]);

    printf("Cone with a %d degree angle\n",(int)parameter);
    printf("Line passing through the point (%d, %d, %d) and parallel to the vector (%d, %d, %d)\n",
           (int)(xp), (int)(yp), (int)(zp), (int)(xv), (int)(yv), (int)(zv));

    PI = 3.141592653589;
    float ang = (parameter * PI) / 180.0;
    float a = powf(xv, 2) + powf(yv, 2) - (powf(zv, 2) * powf(tanf(ang), 2));
    float b = 2 * ((xp * xv) + (yp * yv) - (zp * zv * powf(tanf(ang), 2)));
    float c = powf(xp, 2) + powf(yp, 2) - (powf(zp, 2) * powf(tanf(ang), 2));

    float del = b * b - (4 * a * c);

    if (del < 0)
        printf("No intersection point.\n");
    if (del == 0) {
        float sol = (-b) / (2 * a);
        printf("1 intersection point:\n");
	printf("(%.3f, %.3f, %.3f)\n", (sol * xv) + xp, (sol * yv) + yp, (sol * zv) + zp);
    }
    if (del > 0) {
        float sol1 = ((-b) + sqrtf(del)) / (2 * a);
        float sol2 = ((-b) - sqrtf(del)) / (2 * a);
	printf("2 intersection points:\n");
	printf("(%.3f, %.3f, %.3f)\n", (sol1 * xv) + xp, (sol1 * yv) + yp, (sol1 * zv) + zp);
	printf("(%.3f, %.3f, %.3f)\n", (sol2 * xv) + xp, (sol2 * yv) + yp, (sol2 * zv) + zp);
    }
}
