/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "bitmap.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void write_bmp_header(int fd, int size)
{
    bmp_header_t header;
    make_bmp_header(&header, size);
    write(fd, &header, sizeof(header));
}

void write_bmp_info_header(int fd, int size)
{
    bmp_info_header_t info;
    make_bmp_info_header(&info, size);
    write(fd, &info, sizeof(info));
}

void make_bmp_header(bmp_header_t *header, size_t size)
{
    if (header == NULL)
        return;
    header->offset = sizeof(bmp_header_t) + sizeof(bmp_info_header_t);
    header->size = header->offset + (size * size * 4);
    header->magic = 0x4D42;
    header->_app1 = 0;
    header->_app2 = 0;
}

void make_bmp_info_header(bmp_info_header_t *header, size_t size)
{
    if (header == NULL)
        return;
    header->size = 40;
    header->width = size;
    header->height = size;
    header->planes = 1;
    header->bpp = 32;
    header->compression = 0;
    header->raw_data_size = size * size * 4;
    header->h_resolution = 0;
    header->v_resolution = 0;
    header->palette_size = 0;
    header->important_colors = 0;
}