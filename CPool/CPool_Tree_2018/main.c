#include "tree.c"

void my_putchar(char c)
{
    write(1, &c, 1);
}

int main(int argv, char **argc)
{
    tree(5);
}
