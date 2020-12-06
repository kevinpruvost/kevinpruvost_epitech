/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** my.h
*/

#ifndef MY_H
#define MY_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum fun_e {
    EXP,
    COS,
    SIN,
    COSH,
    SINH
} fun_e;

int identify_option(char **av);
int my_strcmp(char *s1, char *s2);
int my_strlen(char *s);
double **mult_matrice(double **matrice1, double **matrice2);
double **add_matrice(double **matrice1, double **matrice2);
long long fact(int nb);
void print_matrice(double **matrice);
double **create_matrice_identity(double nb);
double **create_matrice_1(double nb, char **av);
double **create_matrice_empty(double nb);
double **div_matrice_1(double **matrice, long long int div);
double **copy_matrice(double **matrice);
double **power_matrice(double **matrice, double power);
double **sub_matrice(double **matrice1, double **matrice2);

void exp_case(double **matrice_1, double taille);
void cos_case(double **matrice_1, double taille);
void sin_case(double **matrice_1, double taille);
void cosh_case(double **matrice_1, double taille);
void sinh_case(double **matrice_1, double taille);

#endif
