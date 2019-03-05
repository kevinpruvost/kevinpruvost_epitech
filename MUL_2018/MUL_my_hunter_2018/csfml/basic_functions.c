/*
** EPITECH PROJECT, 2018
** basic_functions.c
** File description:
** first csfml funcs
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/my.h"

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height)
{
    framebuffer_t *fb;

    fb = malloc(sizeof(framebuffer_t));
    fb->pixels = malloc(width * height * 4);
    fb->width = width;
    fb->height = height;

    return (fb);
}

void put_pixel(unsigned int x, unsigned int y, sfColor color, framebuffer_t *fb)
{
    int position = ((fb->width) * (x - 1) + y - 1) * 4;

    fb->pixels[position] = color.r;
    fb->pixels[position+1] = color.g;
    fb->pixels[position+2] = color.b;
    fb->pixels[position+3] = color.a;
}
