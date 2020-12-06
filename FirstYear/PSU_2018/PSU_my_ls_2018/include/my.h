/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** includes
*/

#ifndef MY_H_
#define MY_H_

#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

void help_option(void);

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
void ilsa(struct stat *statbuf);
void minor_major(struct stat *statbuf);
void name_type(char *name, struct stat *statbuf);
int info_file(char *file_name);
char *info_file_name(char *file_name);

typedef struct file_t {
    char *name;
    char *t_name;
    char *time;
    struct stat *statbuf;
    struct file_t *next;
} file_t;

typedef struct dir_t {
    char *name;
    char *t_name;
    char *time;
    struct file_t *files;
    struct stat *statbuf;
    struct dir_t *next;
    struct dir_t *sub;
} dir_t;

typedef struct opt {
    int R_o;
    int r_o;
    int d_o;
    int t_o;
    int l_o;
} opt_t;

int my_rev_dir(dir_t **);
int my_rev_files(file_t **);
dir_t *create_dir(char *name, int);
file_t *create_file(char *name);
file_t *add_file(file_t *files, char *name);
dir_t *add_dir(dir_t *dir, char *name, int);
int print_dir_t(dir_t *dir, int, int);
void print_file_t(file_t *file, int);
dir_t *sort_dir_t(dir_t *dir, int mode);
int compare_str(char *s1, char *s2);
file_t *sort_file_t(file_t *dir, int mode);
dir_t *comp_exchange_dir(dir_t *, dir_t *);
file_t *comp_exchange_file(file_t *, file_t *);

int print_dir_t_no(dir_t *dir, int, int);
void reverse_print_file_t_nor(file_t *, int);
char *correct_time(char *time);
char *format(char *dir, char *file);

int is_dir(char *name);
char **str_add_to_array(char *, char **);
int my_arraylen(char **);
int options_identify_no_dir(char *str, opt_t *options, int);
int options_identify_dir(opt_t *options, char **str_array);
int check_valid_options(char *options);
void manage_arg(char *, opt_t *, char **);
int info_dir_no_option(char *);
opt_t *attrib_options(opt_t *, char *);

dir_t *init_dir(dir_t *dir, struct stat *statbuf, char *name);
dir_t *process_dir(dir_t *dir, int mode, struct dirent *dp, DIR *pointer);

dir_t *exchange_place_dir(dir_t *init, dir_t *dir);
file_t *sort_file_t_time(file_t *dir);
dir_t *sort_dir_t_time(dir_t *dir);
file_t *exchange_place(file_t *init, file_t *dir);
dir_t *exchange_place_dir(dir_t *init, dir_t *dir);

void reverse_print_dir_t_no(dir_t *dir, int);
void reverse_print_dir_t(dir_t *dir, int);
dir_t *only_dir(dir_t *dir);
void print_l_dir(dir_t *dir, int);
void print_l_file(file_t *file, int);
void print_rights(struct stat *statbuf);
int print_owners(struct stat *, char *, int);

dir_t *reverse_all(dir_t *dir);

int error_management(char **);
char *options_create(void);

#endif
