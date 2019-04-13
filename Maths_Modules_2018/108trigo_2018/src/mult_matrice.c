/*
** EPITECH PROJECT, 2019
** mult_matrice.c
** File description:
** mult matrice
*/

#include "my.h"

int error_management_mult_matrice(double **matrice1, double **matrice2)
{
    int	nb_lin1 = 0;
    int	nb_col1 = 0;
    int	nb_lin2 = 0;
    int	nb_col2 = 0;
    
    for (; matrice1[nb_lin1] != NULL; nb_lin1++);
    for (; matrice1[0][nb_col1] != 0; nb_col1++);
    for	(; matrice2[nb_lin2] != NULL; nb_lin2++);
    for	(; matrice2[0][nb_col2] != 0; nb_col2++);

    if (nb_lin2 != nb_col1)
        return (84);
    return (0);
}

double **copy_matrice(double **matrice)
{
    int taille = 0;
    double **new_matrice;

    for (; matrice[taille] != NULL; taille++);
    new_matrice = malloc(sizeof(double *) * (taille + 1));
    for (int i = 0; i < taille; i++) {
        new_matrice[i] = malloc(sizeof(double) * (taille + 1));
        for (int j = 0; j < taille; j++) {
            new_matrice[i][j] = matrice[i][j];
        }
    }
    return (new_matrice);
}

double **div_matrice_1(double **matrice, long long div)
{
    int taille = 0;
    long long mem = 0;

    for (; matrice[taille] != NULL; taille++);
    for (int i = 0; i < taille; i++)
        for (int j = 0; j < taille; j++) {
            for (int k = 1; k <= div; k++) 
                matrice[i][j] /= (double)(k);
        }
    return (matrice);
}

double **power_matrice(double **matrice, double power)
{
    int taille = 0;
    double **matrice_base = copy_matrice(matrice);

    if (power < 0)
        return (NULL);
    for (; matrice[taille] != NULL; taille++);
    if (power == 0) {
        matrice = create_matrice_identity(taille);
        return (matrice);
    }
    for (int i = 1; i < power; i++)
        matrice = mult_matrice(matrice, matrice_base);
    return (matrice);
}

double **add_matrice(double **matrice1, double **matrice2)
{
    double **matrice_resultat;
    int nb_lin1 = 0;
    int nb_col1 = 0;
    int nb_lin2 = 0;
    int nb_col2 = 0;

    for (; matrice1[nb_lin1] != NULL; nb_lin1++);
    for (; matrice2[nb_lin2] != NULL; nb_lin2++);
    for (; matrice2[0][nb_col2] != 0; nb_col2++);

    matrice_resultat = malloc(sizeof(double *) * (nb_lin1 + 1));
    for (int i = 0; i < nb_lin1; i++) {
        matrice_resultat[i] = malloc(sizeof(double) * (nb_lin1 + 1));
        for (int j = 0; j < nb_lin1; j++) {
            matrice_resultat[i][j] = matrice1[i][j] + matrice2[i][j];
        }
    }
    return (matrice_resultat);
}

double **sub_matrice(double **matrice1, double **matrice2)
{
    double **matrice_resultat;
    int nb_lin1 = 0;
    int nb_col1 = 0;
    int nb_lin2 = 0;
    int nb_col2 = 0;

    for (; matrice1[nb_lin1] != NULL; nb_lin1++);
    for (; matrice2[nb_lin2] != NULL; nb_lin2++);
    for (; matrice2[0][nb_col2] != 0; nb_col2++);

    matrice_resultat = malloc(sizeof(double *) * (nb_lin1 + 1));
    for (int i = 0; i < nb_lin1; i++) {
        matrice_resultat[i] = malloc(sizeof(double) * (nb_lin1 + 1));
        for (int j = 0; j < nb_lin1; j++) {
            matrice_resultat[i][j] = matrice1[i][j] - matrice2[i][j];
        }
    }
    return (matrice_resultat);
}

double **mult_matrice(double **matrice1, double **matrice2)
{
    double **matrice_resultat;
    int nb_lin1 = 0;
    int nb_col1 = 0;
    int nb_lin2 = 0;
    int nb_col2 = 0;

    for (; matrice1[nb_lin1] != NULL; nb_lin1++);
    for (; matrice2[nb_lin2] != NULL; nb_lin2++);
    for (; matrice2[0][nb_col2] != 0; nb_col2++);

    matrice_resultat = malloc(sizeof(double *) * (nb_lin1 + 1));
    for (int i = 0; i < nb_lin1; i++) {
        matrice_resultat[i] = malloc(sizeof(double) * (nb_lin1 + 1));
        for (int j = 0; j < nb_lin1; j++) {
            matrice_resultat[i][j] = 0;
            for (int k = 0; k < nb_lin1; k++)
                matrice_resultat[i][j] += matrice1[i][k] * matrice2[k][j];
        }
    }
    return (matrice_resultat);
}
