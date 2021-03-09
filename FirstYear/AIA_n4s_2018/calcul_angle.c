/*
** EPITECH PROJECT, 2019
** calcul_angle.c
** File description:
** calcul angle
*/

#include "my.h"

#define PI 3.1415926535897932384626433

double calcul_angle(double p1, double p2, float ang1, float ang2)
{
    double ret = PI / 180;
    double ang_use = ang1 * ret;
    double C = sqrt(pow(p2, 2) + pow(p1, 2) - (2 * p2 * p1) * cos(ang_use));
    double ang = (p2 - p1 * cos(ang_use)) / C;

    ang = acos(ang);
    ang *= (180 / PI);
    return (ang);
}

double mult_parallel(double p1, double p2, float ang1, float ang2)
{
    double ang_triangle = calcul_angle(p1, p2, ang1, ang2);
    double ang_counter = ang1 + ang2;
    double direction = (ang_triangle + ang_counter - 180) / 180;
    char *line = create_string(100);

    if (p1 >= 2000 && p2 >= 2000)
        return (84);
    return (direction);
}
