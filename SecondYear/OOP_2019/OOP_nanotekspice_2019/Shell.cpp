/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Shell
*/

#include "Shell.hpp"

void Shell::AddRegex(std::string & line)
{
    std::regex find("\\s?(\\w+)=(\\w+)\\s?");
    std::smatch match;
    nts::Tristate result;

    if (std::regex_search(line, match, find)) {
        if (match.str(1).empty())
            throw EXCEPTION("Invalid Input");
        if (match.str(2).empty() || match.str(2) == "U")
            result = nts::Tristate::UNDEFINED;
        else if (match.str(2) == "0")
            result = nts::Tristate::FALSE;
        else if (match.str(2) == "1")
            result = nts::Tristate::TRUE;
        else
            throw EXCEPTION("Invalid Input");
        _circuit.inputValue(match.str(1), result);
    } else
        throw EXCEPTION("Invalid Input");
}

bool isTrue(int num)
{
    static bool is;
    if (num == 0)
        is = false;
    if (num == 1)
        is = true;
    return is;
}

void signalHandler(int signum)
{
    if (signum == 2)
        isTrue(1);
}

void Shell::Loop(void)
{
    isTrue(0);
    _circuit.simulate();
    usleep(200000);
    signal((int)SIGINT, signalHandler);
    if (isTrue(5))
        _loop = false;
    isTrue(0);
}

void Shell::Read(void)
{
    if (_loop)
    {
        Loop();
        return;
    }

    std::string line;
    std::smatch match;

    std::cout << "> ";
    std::getline(std::cin, line);
    if (line.find("exit\0") == 0 || line.empty())
    {
        _rep = false;
        return;
    }
    else if (line.find("simulate\0") == 0)
        _circuit.simulate();
    else if (line.find("display\0") == 0)
        _circuit.display();
    else if (line.find("dump\0") == 0)
        _circuit.dump();
    else if (std::regex_search(line, match, std::regex {"(=)"}))
        AddRegex(line);
    else if (line.find("loop\0") == 0)
        _loop = true;
    else
        throw EXCEPTION("Command not found");
    line.clear();
}

Shell::Shell(nts::Circuit & circuit)
    : _circuit { circuit }
    , _loop { false }
    , _rep { true }
{
}

bool Shell::takeCommand()
{
    try {
        Read();
    } catch (const std::exception& error) {
        std::cout << error.what() << std::endl;
        _rep = false;
    }
    return _rep;
}

Shell::~Shell()
{
}