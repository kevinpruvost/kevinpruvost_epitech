/*
** EPITECH PROJECT, 2020
** type.c
** File description:
** type
*/

#include "nm.h"

#include <string.h>

char type32_2(Elf32_Shdr * shdr, Elf32_Sym * sym)
{
    char c = 0;

    (sym->st_shndx == SHN_UNDEF) ? c = 'U' : 0;
    (sym->st_shndx == SHN_ABS && c == 0) ? c = 'A' : 0;
    (sym->st_shndx == SHN_COMMON && c == 0) ? c = 'C' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_NOBITS &&
        shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) ? c = 'B' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
        shdr[sym->st_shndx].sh_flags == SHF_ALLOC) ? c = 'R' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
        shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) ? c = 'D' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
        shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) ?
        c = 'T' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_DYNAMIC) ? c = 'D' : 0;
    return c;
}

char type32(Elf32_Ehdr * ehdr, Elf32_Shdr * shdr, Elf32_Sym * sym)
{
    char c = 0;

    (ELF32_ST_BIND(sym->st_info) == STB_GNU_UNIQUE) ? c = 'u' : 0;
    (c == 0 && ELF32_ST_BIND(sym->st_info) == STB_WEAK) ?
        (c = (sym->st_shndx == SHN_UNDEF) ? 'w' : 'W') : 0;
    (c == 0 && ELF32_ST_BIND(sym->st_info) == STB_WEAK
        && ELF32_ST_TYPE(sym->st_info) == STT_OBJECT) ?
        (c = (sym->st_shndx == SHN_UNDEF) ? 'v' : 'V') : 0;
    (c == 0) ? c = type32_2(shdr, sym) : 0;
    if (c == 0 &&
        (strcmp(&SECT_NAME[shdr[sym->st_shndx].sh_name], ".init_array") ||
        strcmp(&SECT_NAME[shdr[sym->st_shndx].sh_name], ".fini_array")))
        c = 'T';
    if (ELF32_ST_BIND(sym->st_info) == STB_LOCAL && c != 0)
        c += 32;
    return c;
}

char type64_2(Elf64_Shdr * shdr, Elf64_Sym * sym)
{
    char c = 0;

    (sym->st_shndx == SHN_UNDEF) ? c = 'U' : 0;
    (sym->st_shndx == SHN_ABS && c == 0) ? c = 'A' : 0;
    (sym->st_shndx == SHN_COMMON && c == 0) ? c = 'C' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_NOBITS &&
        shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) ? c = 'B' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
        shdr[sym->st_shndx].sh_flags == SHF_ALLOC) ? c = 'R' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
        shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) ? c = 'D' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_PROGBITS &&
        shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) ?
        c = 'T' : 0;
    (c == 0 && shdr[sym->st_shndx].sh_type == SHT_DYNAMIC) ? c = 'D' : 0;
    return c;
}

char type64(Elf64_Ehdr * ehdr, Elf64_Shdr * shdr, Elf64_Sym * sym)
{
    char c = 0;

    (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE) ? c = 'u' : 0;
    (c == 0 && ELF64_ST_BIND(sym->st_info) == STB_WEAK) ?
        (c = (sym->st_shndx == SHN_UNDEF) ? 'w' : 'W') : 0;
    (c == 0 && ELF64_ST_BIND(sym->st_info) == STB_WEAK
        && ELF64_ST_TYPE(sym->st_info) == STT_OBJECT) ?
        (c = (sym->st_shndx == SHN_UNDEF) ? 'v' : 'V') : 0;
    (c == 0) ? c = type64_2(shdr, sym) : 0;
    if (c == 0 &&
        (strcmp(&SECT_NAME[shdr[sym->st_shndx].sh_name], ".init_array") ||
        strcmp(&SECT_NAME[shdr[sym->st_shndx].sh_name], ".fini_array")))
        c = 'T';
    if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
        c += 32;
    return c;
}