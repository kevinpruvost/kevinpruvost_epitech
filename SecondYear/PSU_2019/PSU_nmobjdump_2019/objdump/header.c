/*
** EPITECH PROJECT, 2020
** header.c
** File description:
** header
*/

#include "objdump.h"

static void display_flags(int e_flags)
{
    char *str = "";
    static type_t flags[] = {
        {HAS_RELOC, "HAS_RELOC"}, {EXEC_P, "EXEC_P"},
        {HAS_LINENO, "HAS_LINENO"}, {HAS_DEBUG, "HAS_DEBUG"},
        {HAS_SYMS, "HAS_SYMS"}, {HAS_LOCALS, "HAS_LOCALS"},
        {DYNAMIC, "DYNAMIC"}, {WP_TEXT, "WP_TEXT"},
        {D_PAGED, "D_PAGED"}, {BFD_IS_R, "BFD_IS_RELAXABLE"},
        {HAS_LOAD_PAGE, "HAS_LOAD_PAGE"},
    };

    for (int i = 0; i < (int)(sizeof(flags) / sizeof(*flags)); ++i) {
        if (e_flags & flags[i].id) {
            printf("%s%s", str, flags[i].value);
            str = ", ";
        }
    }
}

static char *get_architecture(int e_machine)
{
    static type_t mach[] = {
        {EM_386, "i386"},
        {EM_X86_64, "i386:x86-64"},
    };

    for (int i = 0; i < (int)(sizeof(mach) / sizeof(*mach)); ++i) {
        if (mach[i].id == e_machine)
            return (mach[i].value);
    }
    return ("Unknown");
}

void display_header32(nm_t *nm)
{
    printf("\n%s:     file format elf32-i386\n", nm->filename);
    printf("architecture: %s, flags 0x%08x:\n",
    get_architecture(nm->ehdr32->e_machine), nm->ehdr32->e_flags);
    display_flags(nm->ehdr32->e_flags);
    printf("\nstart address 0x%08x\n\n", nm->ehdr32->e_entry);
}

void display_header64(nm_t *nm)
{
    printf("\n%s:     file format elf64-x86-64\n", nm->filename);
    printf("architecture: %s, flags 0x%08x:\n",
    get_architecture(nm->ehdr64->e_machine), nm->ehdr64->e_flags);
    display_flags(nm->ehdr64->e_flags);
    printf("\nstart address 0x%016lx\n\n", nm->ehdr64->e_entry);
}

void display_header(nm_t * nm)
{
    if (nm->arch == A32)
        display_header32(nm);
    else
        display_header64(nm);
}