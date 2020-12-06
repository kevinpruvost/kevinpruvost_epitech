/*
** EPITECH PROJECT, 2020
** read_section.c
** File description:
** read section
*/

#include "objdump.h"

void print_hex(uint8_t * data, int size)
{
    for (int i = 0; i < 16; ++i) {
        (i < size) ? printf("%02x", data[i]) : printf("  ");
        (!((i + 1) % 4)) ? printf(" ") : 0;
    }
    printf(" ");
    for (int i = 0; i < 16; ++i) {
        (i < size) ? printf("%c", data[i] >= 32 && data[i] <= 126 ?
    data[i] : '.') : printf(" ");
    }
}

void read_section32(Elf32_Ehdr * ehdr, Elf32_Shdr shdr)
{
    for (unsigned int i = shdr.sh_offset;
    i < (unsigned int)(shdr.sh_offset + shdr.sh_size); i += 16) {
        printf(" %04x ", (int)(shdr.sh_addr + i - shdr.sh_offset));
        print_hex((void *)ehdr + i, shdr.sh_offset + shdr.sh_size - i);
        printf("\n");
    }
}

void read_section64(Elf64_Ehdr * ehdr, Elf64_Shdr shdr)
{
    for (unsigned int i = shdr.sh_offset;
    i < (unsigned int)(shdr.sh_offset + shdr.sh_size); i += 16) {
        printf(" %04x ", (int)(shdr.sh_addr + i - shdr.sh_offset));
        print_hex((void *)ehdr + i, shdr.sh_offset + shdr.sh_size - i);
        printf("\n");
    }
}