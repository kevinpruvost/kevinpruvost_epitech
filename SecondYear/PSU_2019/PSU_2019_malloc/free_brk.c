/*
** EPITECH PROJECT, 2020
** free_brk.c
** File description:
** free brk
*/

#include "libmy_malloc.h"

static mem_t *pre_mem(mem_t * c)
{
    static mem_t *pre = NULL;

    if (c != GET)
        pre = c;
    return (pre);
}

void free_brk2(mem_t * begin)
{
    mem_t *pre = pre_mem(GET);

    if (base_mem(GET) == begin)
        base_mem(NULL);
    while (pre != NULL && pre->next != begin)
        pre = pre->next;
    if (pre != NULL && pre->next == begin)
        pre->next = NULL;
    my_brk(begin);
}

void separate_free_brk(mem_t *baseBrk)
{
    mem_t *new;
    long size = getmpagesize();

    while (size <= baseBrk->size + MEM_T_SIZE)
        size += (getmpagesize());
    size -= getmpagesize();
    if (size == 0)
        return;
    baseBrk->size -= size;
    new = ((void *)(baseBrk + 1)) + baseBrk->size;
    baseBrk->next = new;
    new->size = size;
    new->freed = true;
    new->next = NULL;
}

void pre_free_brk(mem_t *baseBrk)
{
    while (baseBrk != NULL) {
        if (baseBrk->freed == true && baseBrk->next != NULL
        && baseBrk->next->freed == true) {
            baseBrk->size += (MEM_T_SIZE + baseBrk->next->size);
            baseBrk->next = baseBrk->next->next;
        } else
            baseBrk = baseBrk->next;
    }
    baseBrk = base_mem(GET);
    while (baseBrk != NULL && baseBrk->next != NULL)
        baseBrk = baseBrk->next;
    if (baseBrk != NULL && baseBrk->freed == true
        && (int)baseBrk->size > getmpagesize())
        separate_free_brk(baseBrk);
}

void free_brk(mem_t *baseBrk)
{
    long sizeToFree = 0;
    void *begin = NULL;

    if (base_mem(GET) == NULL)
        return;
    pre_mem(baseBrk);
    pre_free_brk(base_mem(GET));
    while (baseBrk != NULL && baseBrk->next != NULL)
        baseBrk = baseBrk->next;
    if (baseBrk != NULL && baseBrk->freed == true) {
        sizeToFree = baseBrk->size + MEM_T_SIZE;
        begin = baseBrk;
    }
    if ((int)sizeToFree >= getmpagesize())
        free_brk2(begin);
    pre_mem(NULL);
}