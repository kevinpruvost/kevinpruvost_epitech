/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Shell
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

#include "Circuit.hpp"

#include <string>
#include <iostream>
#include <algorithm>
#include <regex>
#include <iostream>
#include <csignal>
#include <unistd.h>

class Shell {
    public:
        Shell(nts::Circuit & circuit);
        ~Shell();

        void Loop(void);
        void Read();
        void AddRegex(std::string & line);
        bool takeCommand();

    private:
        nts::Circuit & _circuit;
        bool _loop;
        bool _rep;
};

#endif /* !SHELL_HPP_ */
