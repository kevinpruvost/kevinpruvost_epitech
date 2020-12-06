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
#include <string>
#include <utility>
#include <algorithm>
#include <iomanip>

void get_temp()
{
    std::string str;
    std::getline(std::cin, str);
    std::string num = str.substr(0, str.find(' '));
    if (num == str)
        return;
    std::string rest = str.substr(str.find(' ') + 1, str.length());
    double degree = std::stod(num);
    std::ostringstream out;
    std::transform(rest.begin(), rest.end(), rest.begin(), ::tolower);
    if (rest.find("celsius") != std::string::npos)
    {
        degree = degree * (9.0 / 5.0) + 32;
        out << std::fixed << std::setprecision(3) << degree;
        std::string degString = out.str();
        std::cout << std::right << std::setw(16) << degString
                  << "      Fahrenheit\n";
    }
    else if (rest.find("fahrenheit") != std::string::npos)
    {
        degree = 5.0 / 9.0 * (degree - 32);
        out << std::fixed << std::setprecision(3) << degree;
        std::string degString = out.str();
        std::cout << std::right << std::setw(16) << degString
                  << "         Celsius\n";
    }
    else
        exit(EXIT_FAILURE);
}

int main(void)
{
    get_temp();
    return EXIT_SUCCESS;
}
