/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** header
*/

#ifndef MY_H
#define MY_H

#include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

typedef struct ai_s {
    float dist[32];
    float res[32];
    char *order;
    char *opt;
    float wheels_dir;
    float f_speed;
    float b_speed;
    int launch;
} ai_t;

float my_getfloat(char *toconvert);

int help_option(char **av, int n);
void my_dprintf(int fd, char *str, ...);
char *create_string(int len);

char *get_next_line(int fd);
int my_strlen(char *s);
void my_putstr_error(char *s);
void my_putstr_error_n(char *s);
void my_putstr_input(char *s);
void my_putstr(char *s);
int my_strcmp(char *s, char *s1);

char *get_add_info(char *line);
char *get_str_add(char *line);
char *get_track(char *line);

int detect_end(char *line, ai_t *w);

int launch_command(char *cmd, ai_t *w);

int get_info_lidar(ai_t *w);
int wheels_dir(ai_t *w, float value);
int car_forward(ai_t *w, float value);
int car_backwards(ai_t *w, float value);
int cycle_wait(ai_t *w);

float detect_collision_front(ai_t *w);
float detect_collision_back(ai_t *w);
float detect_collision_wheel(ai_t *w, float f, float b);

ai_t *create_ai_t(void);
void destroy_ai_t(ai_t *w);

int ai(ai_t *w);

void put_distance(char *line, ai_t *w);

int print_dist(ai_t *w);

double mult_parallel(double p1, double p2, float ang1, float ang2);

void redirected(ai_t *w);

float right_calculate(ai_t *w);
float left_calculate(ai_t *w);

#endif//MY_H
