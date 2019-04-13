/*
** EPITECH PROJECT, 2019
** calculs.c
** File description:
** calculs funcs
*/

#include "my.h"

long long fact(int nb)
{
    long long result = 1;

    if (nb <= 0)
        return (0);
    for (int i = 2; i <= nb; i++) {
        result *= i;
    }
    return (result);
}

void exp_case(double **matrice_1, double taille)
{
    double **result;
    double **mat_id = create_matrice_identity(taille);
    double **mat_for;

    result = add_matrice(mat_id, matrice_1);
    for (int i = 2; i <= 50; i++) {
        mat_for = power_matrice(matrice_1, i);
        mat_for = div_matrice_1(mat_for, i);
        result = add_matrice(result, mat_for);
    }
    print_matrice(result);
}

void cos_case(double **matrice_1, double taille)
{
    double **result;
    double **mat_id = create_matrice_identity(taille);
    double **mat_for;
    int sign = -1;

    result = mat_id;
    for (int i = 2; i <= 50; i += 2) {
        mat_for = power_matrice(matrice_1, i);
        mat_for = div_matrice_1(mat_for, i);
        if (sign == -1)
            result = sub_matrice(result, mat_for);
        else
            result = add_matrice(result, mat_for);
        sign *= -1;
    }
    print_matrice(result);
}

void sin_case(double **matrice_1, double taille)
{
    double **result;
    double **mat_id = create_matrice_identity(taille);
    double **mat_for;
    int sign = -1;

    result = matrice_1;
    for (int i = 3; i <= 50; i += 2) {
        mat_for = power_matrice(matrice_1, i);
        mat_for = div_matrice_1(mat_for, i);
        if (sign == -1)
            result = sub_matrice(result, mat_for);
        else
            result = add_matrice(result, mat_for);
        sign *= -1;
    }
    print_matrice(result);
}

void cosh_case(double **matrice_1, double taille)
{
    double **result;
    double **mat_id = create_matrice_identity(taille);
    double **mat_for;

    result = mat_id;
    for (int i = 2; i <= 50; i += 2) {
        mat_for = power_matrice(matrice_1, i);
        mat_for = div_matrice_1(mat_for, i);
        result = add_matrice(result, mat_for);
    }
    print_matrice(result);
}

void sinh_case(double **matrice_1, double taille)
{
    double **result;
    double **mat_id = create_matrice_identity(taille);
    double **mat_for;

    result = matrice_1;
    for (int i = 3; i <= 50; i += 2) {
        mat_for = power_matrice(matrice_1, i);
        mat_for = div_matrice_1(mat_for, i);
        result = add_matrice(result, mat_for);
    }
    print_matrice(result);
}
