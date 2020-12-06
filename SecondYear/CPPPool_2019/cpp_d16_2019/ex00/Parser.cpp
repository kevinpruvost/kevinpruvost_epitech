/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Parser.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <cstring>

Parser::Parser()
{

}

void Parser::reset()
{
    _result = 0;
}

int Parser::result() const
{
    return _result;
}

bool Parser::isOperand(const char c)
{
    switch (c)
    {
        case '(':
            _operators.push(OPEN);
            return true;
            break;
        case ')':
            _operators.push(CLOSE);
            break;
        case '+':
            _operators.push(ADD);
            return true;
            break;
        case '-':
            _operators.push(SUB);
            return true;
            break;
        case '*':
            _operators.push(MUL);
            return true;
            break;
        case '%':
            _operators.push(MOD);
            return true;
            break;
        case '/':
            _operators.push(DIV);
            return true;
            break;
    }
    return false;
}

int Parser::operation(int num1, const int num2, Operators d)
{
    switch (d)
    {
        case ADD:
            num1 += num2;
            break;
        case SUB:
            num1 -= num2;
            break;
        case MUL:
            num1 *= num2;
            break;
        case DIV:
            num1 /= num2;
            break;
        case MOD:
            num1 %= num2;
            break;
        default:
            break;
    }
    return num1;
}

void Parser::compute()
{
    while (_operators.top() == CLOSE)
        _operators.pop();

    int num = _operands.top();
    _operands.pop();
    while (_operators.size() > 0 && _operators.top() != OPEN
                                 && _operands.size() > 0)
    {
        const auto ope = _operators.top();
        _operators.pop();
        auto num2 = _operands.top();
        _operands.pop();

        num = operation(num2, num, ope);
    }
    if (_operators.size() != 0 && _operators.top() == OPEN)
        _operators.pop();
    _operands.push(num);
}

void Parser::print()
{
    while (_operands.size() > 0)
    {
        std::cout << _operands.top() << " ";
        _operands.pop();
    }
    std::cout << std::endl;
    while (_operators.size() > 0)
    {
        std::cout << _operators.top() << " ";
        _operators.pop();
    }

    exit(84);
}

void Parser::feed(const std::string & s)
{
    std::string st = s;
    st.erase(std::remove(st.begin(), st.end(), ' '), st.end());

    const char * str = st.c_str();

    for (int i = 0; str[i] != 0; ++i)
    {
        if (isOperand(str[i]))
            continue;

        if (_operators.size() > 0 && _operators.top() == CLOSE)
        {
            compute();
            continue;
        }

        std::string num;
        num.reserve(s.size());
        while (isdigit(str[i]) != 0 && str[i] != 0)
            num += str[i++];
        --i;
        _operands.push(std::stoi(num));
    }

    while (_operators.size() > 0 || _operands.size() > 1)
        compute();

    _result += _operands.top();
    while (_operands.size() > 0)
        _operands.pop();
    while (_operators.size() > 0)
        _operators.pop();
}
