/*
** EPITECH PROJECT, 2020
** getSymbols.c
** File description:
** get sym
*/

#include "objdump.h"

#include <string.h>

void setnew32(t_list32 * list, Elf32_Sym * sym, nm_t * elf)
{
    Elf32_Ehdr * ehdr = elf->ehdr32;
    Elf32_Shdr * shdr = elf->shdr32;
    Elf32_Shdr * syms = elf->syms32;

    list->sym = sym;
    list->value = sym->st_value;
    if (sym->st_info == STT_SECTION && sym->st_shndx <= ehdr->e_shnum &&
        sym->st_name == 0)
        list->name = &SECT_NAME[shdr[sym->st_shndx].sh_name];
    else
        list->name = &SYMB_NAME[sym->st_name];
}

int getsymlist32(nm_t * elf)
{
    Elf32_Ehdr * ehdr = elf->ehdr32;
    Elf32_Shdr * syms = elf->syms32;

    void * limit = (void *)ehdr + syms->sh_offset + syms->sh_size;
    Elf32_Sym * sym = (void *)ehdr + syms->sh_offset;
    int i = 0;

    for (; (void *)sym < limit; ++sym) {
        if (sym->st_name > 0 && sym->st_info != STT_FILE)
            setnew32(&(elf->sym_list32[i++]), sym, elf);
    }
    memset(&(elf->sym_list32[i]), 0, sizeof(t_list32));
    elf->list_len = i - 1;
    return i - 1;
}

void setnew64(t_list64 * list, Elf64_Sym * sym, nm_t * elf)
{
    Elf64_Ehdr * ehdr = elf->ehdr64;
    Elf64_Shdr * shdr = elf->shdr64;
    Elf64_Shdr * syms = elf->syms64;

    list->sym = sym;
    list->value = sym->st_value;
    if (sym->st_info == STT_SECTION && sym->st_shndx <= ehdr->e_shnum &&
        sym->st_name == 0)
        list->name = &SECT_NAME[shdr[sym->st_shndx].sh_name];
    else
        list->name = &SYMB_NAME[sym->st_name];
}

int getsymlist64(nm_t * elf)
{
    Elf64_Ehdr * ehdr = elf->ehdr64;
    Elf64_Shdr * syms = elf->syms64;

    void * limit = (void *)ehdr + syms->sh_offset + syms->sh_size;
    Elf64_Sym * sym = (void *)ehdr + syms->sh_offset;
    int i = 0;

    for (; (void *)sym < limit; ++sym) {
        if (sym->st_name > 0 && sym->st_info != STT_FILE)
            setnew64(&(elf->sym_list64[i++]), sym, elf);
    }
    memset(&(elf->sym_list64[i]), 0, sizeof(t_list64));
    elf->list_len = i - 1;
    return i - 1;
}