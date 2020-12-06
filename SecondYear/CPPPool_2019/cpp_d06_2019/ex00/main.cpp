/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

// C++ includes
#include <iostream>
#include <fstream>
#include <utility>

int error_management(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "my_cat: Usage: ./my_cat file [...]" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int read_files(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        std::ifstream f1(argv[i]);
        std::string s;
        if (!f1.is_open())
        {
            std::cerr << "my_cat: " << argv[i] << ": No such file or directory"
                      << std::endl;
            return EXIT_FAILURE;
        }

        while (std::getline(f1, s))
            std::cout << s << std::endl;

        f1.close();
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (error_management(argc, argv) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (read_files(argc, argv) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
