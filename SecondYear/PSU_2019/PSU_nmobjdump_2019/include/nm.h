/*
** EPITECH PROJECT, 2020
** nm.h
** File description:
** nm
*/

#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdbool.h>

#include "myerror.h"

#define MAGIC_NUMBER "\177ELF"

#define SYMB_NAME ((char *)ehdr + shdr[syms->sh_link].sh_offset)
#define SECT_NAME ((char *)ehdr + shdr[ehdr->e_shstrndx].sh_offset)

typedef enum Archs
{
    A32,
    A64
} Archs;

typedef struct s_list32
{
    Elf32_Sym * sym;
    char * name;
    unsigned int value;
    char type;
} t_list32;

typedef struct s_list64
{
    Elf64_Sym * sym;
    char * name;
    unsigned int value;
    char type;
} t_list64;

typedef struct nm
{
    Elf64_Ehdr * ehdr64;
    Elf64_Shdr * shdr64;
    Elf64_Shdr * syms64;
    Elf32_Ehdr * ehdr32;
    Elf32_Shdr * shdr32;
    Elf32_Shdr * syms32;
    t_list64 * sym_list64;
    t_list32 * sym_list32;
    long int list_len;
    size_t len;
    Archs arch;
    const char *filename;
} nm_t;

int getsymlist32(nm_t * elf);
int getsymlist64(nm_t * elf);
int read32(nm_t * elf);
int read64(nm_t * elf);
char type32(Elf32_Ehdr * ehdr, Elf32_Shdr * shdr, Elf32_Sym * sym);
char type64(Elf64_Ehdr * ehdr, Elf64_Shdr * shdr, Elf64_Sym * sym);
int sort32(nm_t * elf);
int sort64(nm_t * elf);
int nm(const char * filename, bool multiple);
int pre_open(const char *filename, int *fd, bool multiple, nm_t * elf);