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
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "gnl.h"
#include "get_next_line.h"

typedef struct seps_t {
    char *sep;
    struct seps_t *next;
} seps_t;

typedef struct to_runs_t {
    char *to_run;
    struct to_runs_t *next;
} to_runs_t;

typedef struct args_t {
    char **args;
    struct args_t *next;
} args_t;

typedef struct mini_t {
    char **env;
    to_runs_t *to_runs;
    to_runs_t *to_runs_technical;
    args_t *args;
    seps_t *seps;
    int fd[50][2];
    int use_id;
    pid_t pid;
    int progs;
    int loc;
    int piped;
    int error;
} mini_t;

void iteration_error(mini_t *w);

void parse_seps(mini_t *w, char *str);
void parse_to_runs(mini_t *w, char *str);
void parse_args(mini_t *w, char *str, int quote);

int add_seps(mini_t *w, char *str);
int add_args(mini_t *w, char **str);
int add_to_runs(mini_t *w, char *str);
char *create_test_parse(int i);
int is_sep(char *str, int i);

mini_t *parse_mini(char *str, char **env);
void print_mini_t(mini_t *w);

void launch_program_read(mini_t *w);
void launch_program_write(mini_t *w);
void launch_program_pipe(mini_t *w);

int check_spec_char(char *);
int replace_buffer_char(char *buffer, int i);

void append(char **, char *);
char *my_strcpy(char *);
char **my_arrcpy(char **);
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
int my_strcmp(char *, char *);
char **str_to_word_array(char *);
int my_putstr_error(char *);
void clean_str(char *);
void clean_array(char **);
void my_printf(char *str, ...);
char *create_string(int size);
char **create_char_array(int size_v, int size_h);
int remove_char_from_str(char *str, int id);
char *add_char_to_str(char *str, int pos, char c);
void print_char_array(char **);
void free_char_array(char **);
void my_putstr_fd(char *str, int loc);
char **read_file(char *filepath);
char *load_file_in_mem(char *filepath);
void my_put_errno(mini_t *w);

char **my_exec(int ac, char *av, char **);
void special_programs(char *, char **, mini_t *w);
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
void pwd_oldpwd(mini_t *w, char *);
int setenv_func(char *, char **, mini_t *w);

void special_programs2(char *to_run, char **args, mini_t *w);
void cd_func(char *to_run, char **args, mini_t *w);
int setenv_alpha(char **);
void free_mini_t(mini_t *w);

int launch_programs(mini_t *w);

int pipe_write(mini_t *w);
int pipe_read(mini_t *w);
void iteration_launch_programs_for(mini_t *w);

int dup2m(mini_t *w, int fd);
int closem(mini_t *w, int fd);

int identify_order_program(mini_t *w);

int error_launch_prog(mini_t *w);

int identify_order_program(mini_t *w);
int program_file(char *to_run, char *to_runt, char **args, mini_t *w);

#endif
