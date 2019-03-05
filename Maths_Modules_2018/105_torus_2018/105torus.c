/*
** EPITECH PROJECT, 2019
** 105torus.c
** File description:
** 105 main functions
*/

#include "my.h"

int bissection(double a0, double a1, double a2, double a3, double a4, int precision)
{
    double b1 = 0.0;
    double b2 = 1.0;
    int i = 0;
    double bm = 0.0;
    double f1 = 0.0;
    double fm = 0.0;

    while (i < 1000) {
        if (round(b1 * pow(10, precision)) == round(b2 * pow(10, precision)))
            break;
        bm = (b1 + b2) / 2;
        f1 = (a4 * pow(b1, 4)) + (a3 * pow(b1, 3)) + (a2 * pow(b1, 2)) + (a1 * b1) + a0;
        fm = (a4 * pow(bm, 4)) + (a3 * pow(bm, 3)) + (a2 * pow(bm, 2)) + (a1 * bm) + a0;
//      fm = (4 * a4 * pow(bm, 3)) + (3 * a3 * pow(bm, 2)) + (2 * a2 * bm) + a1;
//      f1 = (4 * a4 * pow(b1, 3)) + (3 * a3 * pow(b1, 2)) + (2 * a2 * b1) + a1;
        if (f1 * fm < 0)
            b2 = bm;
        else
            b1 = bm;
        if (round(b1 * pow(10, precision)) == round(b2 * pow(10, precision)))
            break;
        if (i < precision)
            printf("x = %.*g\n",precision,bm);
        else
            printf("x = %.*f\n",precision,bm);
        i++;
    }
    if (i >= 1000) {
        printf("Trop de calculs.");
        exit(0);
    }
}

int newton(double a0, double a1, double a2, double a3, double a4, int precision)
{
    double b0 = 0.5;
    double b1 = 0.0;
    int i = 0;
    double f1;
    double f2;

    while (i < 1000) {
        f1 = (a4 * pow(b0, 4)) + (a3 * pow(b0, 3)) + (a2 * pow(b0, 2)) + (a1 * b0) + a0;
        f2 = (4 * a4 * pow(b0, 3)) + (3 * a3 * pow(b0, 2)) + (2 * a2 * b0) + a1;
        if (f2 == 0)
            return (84);
        b1 = b0 - (f1/f2);
        printf("x = %.*g\n",precision,b0);
        if (round(b1 * pow(10, precision)) == round(b0 * pow(10, precision)))
            break;
        i++;
        b0 = b1;
    }
    if (i >= 1000) {
        printf("Trop de calculs.");
        exit(0);
    }
}

int secante(double a0, double a1, double a2, double a3, double a4, int precision)
{
    int i = 0;
    double x0 = 0.0;
    double x1 = 1.0;
    double x2 = 0.0;
    double f0;
    double f1;
    
    while (i < 1000) {
        f0 = (a4 * pow(x0, 4)) + (a3 * pow(x0, 3)) + (a2 * pow(x0, 2)) + (a1 * x0) + a0;
	f1 = (a4 * pow(x1, 4)) + (a3 * pow(x1, 3)) + (a2 * pow(x1, 2)) + (a1 * x1) + a0;
        if (f1 - f0 == 0)
            return (84);
        x2 = x1 - ((f1 * (x1 - x0)) / (f1 - f0));
        if (i == 0)
            printf("x = %.*g\n",precision,x2);
        else
            printf("x = %.*f\n",precision,x2);
        if (round(x1 * pow(10, precision)) == round(x2 * pow(10, precision)))
            break;
        i++;
        x0 = x1;
        x1 = x2;
    }
    if (i >= 1000) {
        printf("Trop de calculs.");
        exit(0);
    }
}


int torus(char **av)
{
    int opt = my_atoi(av[1]);
    double a0 = my_getdouble(av[2]);
    double a1 = my_getdouble(av[3]);
    double a2 = my_getdouble(av[4]);
    double a3 = my_getdouble(av[5]);
    double a4 = my_getdouble(av[6]);
    int precision = my_atoi(av[7]);

    if (opt == 1)
        bissection(a0, a1, a2, a3, a4, precision);
    if (opt == 2)
        newton(a0, a1, a2, a3, a4, precision);
    if (opt == 3)
        secante(a0, a1, a2, a3, a4, precision);
    return (0);
}
