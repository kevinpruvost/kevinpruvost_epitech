/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#ifndef PARSER_HPP
#define PARSER_HPP

// Project includes
#include "Circuit.hpp"

// C++ includes
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

class Parser
{
public:
    Parser(const char * filename, nts::Circuit & circuit);

    bool parse();

private:
    bool exec();
    bool verifyChipsetsIsFalse(std::string &fileContent);
    bool verifyLinksIsFalse(std::string & fileContent);

private:
    const char * filename;
    nts::Circuit & _circuit;
};

#endif // PARSER_HPP
