/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** include
*/

#ifndef MY_H_
#define MY_H_

#include <stdlib.h>

float PI;

char *load_file_in_mem(char const *filepath);
int my_atoi(char *);
float my_getfloat(char *);
char *my_getnbr(int);
int my_putstr(char *str);
char *my_revstr(char *);
int my_strlen(char *);
char *str_add(char *, char *);

void cylinder(char **av);
void cone(char **av);
void sphere(char **av);

float delta(float a, float b, float c);

#endif
