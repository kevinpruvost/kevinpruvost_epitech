/*
** EPITECH PROJECT, 2020
** nm.c
** File description:
** nm
*/

#include "objdump.h"

#include <string.h>

static int get_sym64(nm_t * elf)
{
    if (elf->ehdr64->e_type != ET_DYN && elf->ehdr64->e_type != ET_EXEC
    && elf->ehdr64->e_type != ET_REL) {
        fprintf(stderr,
        "my_objdump: %s: file format not recognized\n", elf->filename);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < elf->ehdr64->e_shnum; ++i) {
        if (elf->shdr64[i].sh_type == SHT_SYMTAB)
            elf->syms64 = &(elf->shdr64[i]);
    }
    elf->sym_list64 = calloc(1, sizeof(t_list64) * elf->syms64->sh_size);
    if (elf->sym_list64 == NULL)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int get_sym32(nm_t * elf)
{
    elf->ehdr32 = (Elf32_Ehdr *)elf->ehdr64;
    if (elf->ehdr32->e_type != ET_DYN && elf->ehdr32->e_type != ET_EXEC
    && elf->ehdr32->e_type != ET_REL) {
        fprintf(stderr,
        "my_objdump: %s: file format not recognized\n", elf->filename);
        return EXIT_FAILURE;
    }
    elf->shdr32 = (void *)elf->ehdr32 + elf->ehdr32->e_shoff;
    elf->ehdr32 = malloc(elf->len);
    memcpy(elf->ehdr32, elf->ehdr64, elf->len);

    for (int i = 0; i < elf->ehdr32->e_shnum; ++i) {
        if (elf->shdr32[i].sh_type == SHT_SYMTAB)
            elf->syms32 = &(elf->shdr32[i]);
    }
    elf->sym_list32 = calloc(1, sizeof(t_list32) * elf->syms32->sh_size);
    if (elf->sym_list32 == NULL)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int set_elf2(nm_t * elf)
{
    int nb = 0;

    if (elf->arch == A32) {
        if (get_sym32(elf))
            return EXIT_FAILURE;
        nb = getsymlist32(elf);
        if (nb == -1 || sort32(elf) || read32(elf))
            return EXIT_FAILURE;
    } else {
        if (get_sym64(elf))
            return EXIT_FAILURE;
        nb = getsymlist64(elf);
        if (nb == -1 || sort64(elf) || read64(elf))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int set_elf(nm_t * elf, int fd, const char * fn)
{
    memset(elf, 0, sizeof(nm_t));
    elf->len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    elf->ehdr64 = malloc(elf->len + 1);
    read(fd, elf->ehdr64, elf->len);
    elf->filename = fn;
    ((char *)elf->ehdr64)[elf->len] = 0;
    if (memcmp(elf->ehdr64->e_ident, ELFMAG, strlen(ELFMAG))) {
        fprintf(stderr, "my_objdump: %s: file format not recognized\n", fn);
        return EXIT_FAILURE;
    }
    elf->shdr64 = (void *)elf->ehdr64 + elf->ehdr64->e_shoff;
    elf->arch = (elf->ehdr64->e_ident[EI_CLASS] == ELFCLASS32) ? A32 : A64;
    if (elf->len == (size_t)-1) {
        perror("lseek");
        return EXIT_FAILURE;
    }
    return set_elf2(elf);
}

int objdump(const char * fn)
{
    nm_t elf;
    int ret = EXIT_SUCCESS;
    int fd;
    struct stat s;

    fd = open(fn, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "my_objdump: '%s': No such file\n", fn);
        return EXIT_FAILURE;
    }
    (fstat(fd, &s) || S_ISDIR(s.st_mode)) ? ret = EXIT_FAILURE : 0;
    if (ret != EXIT_FAILURE) {
        (!isarfile(fd)) ? ret = set_elf(&elf, fd, fn) :
        set_elf(&elf, fd, fn);
    } else
        fprintf(stderr, "my_objdump: %s: file format not recognized\n", fn);
    close(fd);
    return ret;
}