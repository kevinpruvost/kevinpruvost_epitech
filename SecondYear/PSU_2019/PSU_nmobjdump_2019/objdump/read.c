/*
** EPITECH PROJECT, 2020
** read.c
** File description:
** read
*/

#include "objdump.h"

#include <string.h>

static bool nodisplay32(Elf32_Ehdr * ehdr, Elf32_Shdr * shdr, int tab)
{
    static char *nodisplay[] = { "", ".bss", ".shstrtab", ".symtab",
        ".strtab", ".rela.text", ".rela.debug_info", ".rela.debug_aranges",
        ".rela.debug_line", ".rela.eh_frame", ".tbss", "__libc_freeres_ptrs",
        NULL};

    if (!shdr[tab].sh_size)
        return (true);
    for (int i = 0; nodisplay[i] != NULL; ++i) {
        if (!strcmp(nodisplay[i], &SECT_NAME[shdr[tab].sh_name]))
            return (true);
    }
    return (false);
}

static bool nodisplay64(Elf64_Ehdr * ehdr, Elf64_Shdr * shdr, int tab)
{
    static char *nodisplay[] = { "", ".bss", ".shstrtab", ".symtab",
        ".strtab", ".rela.text", ".rela.debug_info", ".rela.debug_aranges",
        ".rela.debug_line", ".rela.eh_frame", ".tbss", "__libc_freeres_ptrs",
        NULL};

    if (!shdr[tab].sh_size)
        return (true);
    for (int i = 0; nodisplay[i] != NULL; ++i) {
        if (!strcmp(nodisplay[i], &SECT_NAME[shdr[tab].sh_name]))
            return (true);
    }
    return (false);
}

int read32(nm_t * elf)
{
    (elf->ehdr32->e_type == ET_EXEC) ? elf->ehdr32->e_flags = 274 : 0;
    (elf->ehdr32->e_type == ET_DYN) ? elf->ehdr32->e_flags = 336 : 0;
    (elf->ehdr32->e_type == ET_REL) ? elf->ehdr32->e_flags = 17 : 0;
    display_header(elf);
    for (int i = 0; i < elf->ehdr32->e_shnum; ++i) {
        if (nodisplay32(elf->ehdr32, elf->shdr32, i) == false) {
            printf("Contents of section %s:\n",
            &SECT_NAME32[elf->shdr32[i].sh_name]);
            read_section32(elf->ehdr32, elf->shdr32[i]);
        }
    }
    return EXIT_SUCCESS;
}

int read64(nm_t * elf)
{
    (elf->ehdr64->e_type == ET_EXEC) ? elf->ehdr64->e_flags = 274 : 0;
    (elf->ehdr64->e_type == ET_DYN) ? elf->ehdr64->e_flags = 336 : 0;
    (elf->ehdr64->e_type == ET_REL) ? elf->ehdr64->e_flags = 17 : 0;
    display_header(elf);
    for (int i = 0; i < elf->ehdr64->e_shnum; ++i) {
        if (nodisplay64(elf->ehdr64, elf->shdr64, i) == false) {
            printf("Contents of section %s:\n",
            &SECT_NAME64[elf->shdr64[i].sh_name]);
            read_section64(elf->ehdr64, elf->shdr64[i]);
        }
    }
    return EXIT_SUCCESS;
}