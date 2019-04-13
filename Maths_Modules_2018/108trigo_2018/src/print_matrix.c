/*
** EPITECH PROJECT, 2019
** print_matrix.c
** File description:
** print matrix
*/

#include "my.h"

void print_matrice(double **matrice)
{
    int taille = 0;

    for (; matrice[taille] != NULL; taille++);
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%.2f",matrice[i][j]);
            if (j + 1 < taille)
                printf("\t");
        }
        printf("\n");
    }
}
