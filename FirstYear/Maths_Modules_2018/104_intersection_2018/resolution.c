/*
** EPITECH PROJECT, 2019
** resolution.c
** File description:
** for coeff and delta
*/

#include "my.h"

float delta(float a, float b, float c)
{
    float result = (b * b) - (4 * a * c);

    return (result);
}
