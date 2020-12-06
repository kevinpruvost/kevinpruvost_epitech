/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

int error_management(double **matrice)
{
    int nb_line = 0;

    for (; matrice[nb_line] != NULL; nb_line++);

    for (int i = 0; i < nb_line; i++) {
        for (int j = 0; j < nb_line; j++) {
            if (isnan(matrice[i][j]) == 1 || isinf(matrice[i][j]) == 1)
                return (84);
        }
    }
}

int error_str(int ac, char **av)
{
    for (int i = 2; i < ac; i++) {
        for (int j = 0; av[i][j] != 0; j++) {
            if ((av[i][j] < '0' || av[i][j] > '9')
                && av[i][j] != '.' && av[i][j] != '-')
                return (84);
        }
    }
    return (0);
}

void display_help(void)
{
    const char *usage = "USAGE\n"
        "\t./108trigo fun a0 a1 a2....\n\n";
    const char *desc = "DESCRIPTION\n"
        "\tfun\tfunction to be applied, among at least "
        "'EXP', 'COS', 'SIN', 'COSH'\n"
        "\t\tand 'SINH'\n"
        "\tai\tcoeficients of the matrix\n";

    printf("%s%s", usage, desc);
}

int main(int ac, char **av)
{
    double nb = sqrt(ac - 2);
    int option = 0;
    void (*calculs[5])(double **, double);
    double **matrice;

    if (ac >= 2 && my_strcmp(av[1], "-h") == 1) {
        display_help();
        return (0);
    }
    if ((int)(nb) - nb != 0 || nb > 5 || ac < 3)
        return (84);
    if (error_str(ac, av) == 84)
        return (84);
    option = identify_option(av);
    if (option == 84)
        return (84);
    matrice = create_matrice_1(nb, av);
    if (error_management(matrice) == 84)
        return (84);
    calculs[EXP] = exp_case;
    calculs[COS] = cos_case;
    calculs[SIN] = sin_case;
    calculs[COSH] = cosh_case;
    calculs[SINH] = sinh_case;
    calculs[option](matrice, nb);
    return (0);
}
