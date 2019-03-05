#include "tree.c"

void my_putchar(char c)
{
    write(1, &c, 1);
}

int main(int argv, char **argc)
{
    int ah;

    if (argv == 2)
        ah = atoi(argc[1]);
    else
        return (84);
    tree(ah);
}
