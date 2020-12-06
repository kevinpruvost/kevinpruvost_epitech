/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#ifndef MY_H

typedef struct foo2_t {
    union {
        short unsigned int foo;
        short unsigned int bar;
    };
} foo2_t;

typedef struct foo1_t {
    short unsigned int foo;
    foo2_t bar;
} foo1_t;

typedef struct foo_t {
    union {
        foo1_t foo;
        unsigned int bar;
    };
} foo_t;



#endif