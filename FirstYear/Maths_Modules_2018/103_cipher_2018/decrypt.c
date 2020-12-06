/*
** EPITECH PROJECT, 2018
** decrypt.c
** File description:
** functions for the decryption
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>

float determ_3(int **key)
{
    float determ = 0;
    float a, b, c, d, e, f, g, h, i;

    a = key[0][0], b = key[0][1], c = key[0][2];
    d = key[1][0], e = key[1][1], f = key[1][2];
    g = key[2][0], h = key[2][1], i = key[2][2];

    determ = (a * e * i) + (b * f * g) + (c * d * h) - (c * e * g) - (f * h * a) - (i * b * d);
    return (determ);
}

float determinant_matrice_inverse(int **key, int cote)
{
    float determ = 0;

    if (cote == 2)
        determ = (key[0][0] * key[1][1]) - (key[0][1] * key[1][0]);
    if (cote == 3)
        determ = determ_3(key);
    if (determ == 0)
        exit(84);
    return (determ);
}

float **calcul_inverse_3(float **matrice_inversed, int determ, float **key)
{
    float a, b, c, d, e, f, g, h, i;

    a = key[0][0], b = key[0][1], c = key[0][2];
    d = key[1][0], e = key[1][1], f = key[1][2];
    g = key[2][0], h = key[2][1], i = key[2][2];

    matrice_inversed[0][0] = ((e * i) - (f * h)) / determ;
    matrice_inversed[1][0] = ((f * g) - (d * i)) / determ;
    matrice_inversed[2][0] = ((d * h) - (e * g)) / determ;
    matrice_inversed[0][1] = ((c * h) - (b * i)) / determ;
    matrice_inversed[1][1] = ((a * i) - (c * g)) / determ;
    matrice_inversed[2][1] = ((b * g) - (a * h)) / determ; 
    matrice_inversed[0][2] = ((b * f) - (c * e)) / determ;
    matrice_inversed[1][2] = ((c * d) - (a * f)) / determ;
    matrice_inversed[2][2] = ((a * e) - (b * d)) / determ;
    matrice_inversed[3] = NULL;

    return (matrice_inversed);
}

float **matrice_inverse(float **key, int **key_int)
{
    float **matrice_inversed;
    int nb_lin;
    int nb_col;
    float determ;

    for (; key[nb_lin] != NULL; nb_lin++);
    for (; key[0][nb_col] != 0; nb_col++);

    determ = determinant_matrice_inverse(key_int, nb_lin);
    matrice_inversed = malloc(sizeof(float *) * nb_lin);
    for (int i = 0; i < nb_lin; i++)
        matrice_inversed[i] = malloc(sizeof(float) * nb_lin);
    if (nb_lin == 2) {
        matrice_inversed[0][0] = key[1][1] / determ;
        matrice_inversed[0][1] = -key[0][1] / determ;
        matrice_inversed[1][0] = -key[1][0] / determ;
        matrice_inversed[1][1] = key[0][0] / determ;
    }
    if (nb_lin == 3)
        matrice_inversed = calcul_inverse_3(matrice_inversed, determ, key);
    return (matrice_inversed);
}

float **create_key_f(int **key_int)
{
    float **key;
    int nb_lin = 0;
    int nb_col = 0;

    for (; key_int[nb_lin] != NULL; nb_lin++);
    for (; key_int[0][nb_col] != 0; nb_col++);
    key = malloc(sizeof(float *) * (nb_lin + 1));
    for (int i = 0; i < nb_lin; i++)
        key[i] = malloc(sizeof(float) * nb_lin);
    for (int i = 0; i < nb_lin; i++) {
        for (int j = 0; j < nb_lin; j++) {
            key[i][j] = key_int[i][j];
        }
    }
    key[nb_lin] = NULL;
    return (key);
}

void display_key(float **key)
{
    for (int i = 0; key[i] != NULL; i++) {
        for (int j = 0; key[j] != NULL; j++) {
            printf("%.3f\t",key[i][j]);
        }
        printf("\n");
    }
}

void decrypt(char *cstr, char *ckey)
{
    int **key_int = create_key(ckey);
    float **key = create_key_f(key_int);
    int **str = create_matrix(cstr, key);
    int **result;

    key = matrice_inverse(key, key_int);
    result = mult_matrice_f(str, key);

    printf("Key matrix:\n");
    display_key(key);
    printf("\nDecrypted message:\n");
    for (int i = 0; result[i] != NULL; i++)
        for (int j = 0; key[j] != NULL; j++)
            printf("%c", result[i][j]);
}
