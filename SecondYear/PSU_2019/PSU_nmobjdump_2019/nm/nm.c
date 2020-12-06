/*
** EPITECH PROJECT, 2020
** nm.c
** File description:
** nm
*/

#include "nm.h"

#include <string.h>

static int get_sym64(nm_t * elf)
{
    if (elf->ehdr64->e_type != ET_DYN && elf->ehdr64->e_type != ET_EXEC
    && elf->ehdr64->e_type != ET_REL) {
        fprintf(stderr,
        "my_nm: %s: file format not recognized\n", elf->filename);
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
        "my_nm: %s: file format not recognized\n", elf->filename);
        return EXIT_FAILURE;
    }
    elf->shdr32 = (void *)elf->ehdr32 + elf->ehdr32->e_shoff;
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

int set_elf(nm_t * elf, int fd, void * buf)
{
    elf->ehdr64 = buf;
    if (memcmp(MAGIC_NUMBER, elf->ehdr64->e_ident, sizeof(MAGIC_NUMBER) - 1)) {
        fprintf(stderr, "my_nm: %s: file format not recognized\n",
        elf->filename);
        return EXIT_FAILURE;
    }
    elf->shdr64 = (void *)elf->ehdr64 + elf->ehdr64->e_shoff;
    elf->arch = (elf->ehdr64->e_ident[EI_CLASS] == ELFCLASS32) ? A32 : A64;
    elf->len = lseek(fd, 0, SEEK_END);
    if (elf->len == (size_t)-1) {
        perror("lseek");
        return EXIT_FAILURE;
    }
    return set_elf2(elf);
}

int nm(const char * filename, bool multiple)
{
    nm_t elf;
    int ret = EXIT_SUCCESS;
    int fd;
    void *buf;
    struct stat s;

    if (pre_open(filename, &fd, multiple, &elf) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (fstat(fd, &s) == -1) {
        fprintf(stderr, "my_nm: '%s': No such file\n", filename);
        return EXIT_FAILURE;
    }
    buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buf != (void *)-1) {
        ret = set_elf(&elf, fd, buf);
        munmap(NULL, s.st_size);
    } else
        fprintf(stderr, "my_nm: %s: file format not recognized\n", filename);
    close(fd);
    return ret;
}