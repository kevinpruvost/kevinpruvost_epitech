/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** my
*/

#ifndef MY_H_
#define MY_H_

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include "gnl.h"
#include "get_next_line.h"

char *my_strcpy(char *);
void my_putchar(char c);
int my_put_nbr(int nb);
int my_atoi(char *);
int my_putstr(char *);
int my_strlen(char *);
float my_getfloat(char *toconvert);
char *my_getnbr(int nbr);
char *my_revstr(char *str);
char *str_add(char *base, char *toadd);
char **str_add_to_array(char *, char **);
int my_arraylen(char **array);
int is_str(char *, char *);
char **str_to_word_array(char *);
int my_putstr_error(char *);

char **my_exec(int ac, char *av, char **);
char **special_programs(char *, char **, char **);
char **path_detect(char **, char **);
char **unsetenv_function(char **env, char *arg);
char *str_sk(char *str);
char *env_value(char *env);
char *str_for_my_exec(char *str, char **env);
char **args_for_my_exec(char **args, char *str, char **env);
int identify_cmd(char *str);
int env_var_exist(char **env, char *str);
char **replace_env_setenv(char **env, char *str, char *arg);

char *search_env(char *str, char **env);

void free_path(char **path);

int is_reg_file(char *);

void sigstop(int);
void sigkill(int);

void free_my_exec(char *, char **);
char **pwd_oldpwd(char **, char *);
char **setenv_func(char *, char **, char **);

char **special_programs2(char *to_run, char **args, char **env);
char **cd_func(char *to_run, char **args, char **env);
int setenv_alpha(char **);

#endif
