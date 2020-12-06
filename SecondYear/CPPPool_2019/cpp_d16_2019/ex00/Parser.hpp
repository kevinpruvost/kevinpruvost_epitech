/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <stack>

class Parser
{
    enum Operators
    {
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        OPEN,
        CLOSE
    };

public:
    Parser();

public:
    void feed(const std::string & str);

    int result() const;
    void reset();

private:
    bool isOperand(const char c);
    void compute();

    int operation(int num1, const int num2, Operators d);

    void print();

private:
    int _result = 0;

    std::stack<Operators> _operators;
    std::stack<int> _operands;
};

#endif // PARSER_HPP
