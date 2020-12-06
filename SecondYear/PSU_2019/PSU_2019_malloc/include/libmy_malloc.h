/*
** EPITECH PROJECT, 2020
** libmy header
** File description:
** header
*/

#ifndef LIBMY_MALLOC_H
#define LIBMY_MALLOC_H

#include <unistd.h>
#include <string.h>

void *memset(void *, int, size_t);

#define true 1
#define false 0

#define MEM_T_SIZE (long int)sizeof(mem_t)
#define GET (void *)-1

typedef struct mem_t {
    struct mem_t *next;
    long int size;
    char freed;
} mem_t;

mem_t *base_mem(mem_t *mem);

mem_t *next_ptr(mem_t *ptr);
int getmpagesize(void);

void *my_sbrk(long size);
int my_brk(void *ptr);
long resize(long size);
long resize_power(long size);

mem_t *init_mem(const long size);
void add_empty_mem(mem_t *tmp, size_t size);
void * add_mem(const long size);
void free_mem(void * adress);
void free_brk(mem_t * baseBrk);
void *realloc_ptr(void *ptr, long size, mem_t *baseBrk);
void *calloc_ptr(long nmemb, long size);

void *malloc(size_t);
void free(void *);
void *realloc(void *, size_t);
void *calloc(size_t, size_t);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

int verify_length(void);

#endif