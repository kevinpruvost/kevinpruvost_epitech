/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#ifndef EX00_H
#define EX00_h

typedef struct cthulhu_s cthulhu_t;

typedef struct koala_s koala_t;

typedef struct cthulhu_s {
    int m_power;
    char *m_name;
} cthulhu_t;

cthulhu_t *new_cthulhu(void);
void print_power(cthulhu_t * this);
void attack(cthulhu_t * this);
void sleeping(cthulhu_t * this);

typedef struct koala_s {
    cthulhu_t m_parent;
    char m_is_a_legend;
} koala_t;

koala_t *new_koala(char * name, char is_a_legend);
void eat(koala_t *this);

#endif
