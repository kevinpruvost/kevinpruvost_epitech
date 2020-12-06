/*
** EPITECH PROJECT, 2019
** create_matrix.c
** File description:
** create matrix funcs
*/

#include "my.h"

double **create_matrice_identity(double nb)
{
    double **matrice = malloc(sizeof(double *) * (nb * nb + 1));
    int id = 2;

    for (int i = 0; i < (int)(nb); i++) {
        matrice[i+1] = NULL;
        matrice[i] = malloc(sizeof(double) * (nb * nb + 1));
        for (int j = 0; j < (int)(nb); j++) {
            if (i == j)
                matrice[i][j] = 1;
            else
                matrice[i][j] = 0;
            id++;
        }
    }
    return (matrice);
}

double **create_matrice_1(double nb, char **av)
{
    double **matrice = malloc(sizeof(double *) * (nb * nb + 1));
    int id = 2;

    for (int i = 0; i < (nb); i++) {
        matrice[i] = malloc(sizeof(double) * (nb * nb + 1));
        for (int j = 0; j < (nb); j++) {
            matrice[i][j] = atof(av[id]);
            id++;
	}
    }
    matrice[(int)(nb)] = NULL;
    return (matrice);
}

double **create_matrice_empty(double nb)
{
    double **matrice = malloc(sizeof(double *) * (nb * nb + 1));
    int id = 2;

    for (int i = 0; i < (int)(nb); i++) {
        matrice[i+1] = NULL;
        matrice[i] = malloc(sizeof(double) * (nb * nb + 1));
        for (int j = 0; j < (int)(nb); j++) {
            matrice[i][j] = 0;
            id++;
        }
    }
    return (matrice);
}
