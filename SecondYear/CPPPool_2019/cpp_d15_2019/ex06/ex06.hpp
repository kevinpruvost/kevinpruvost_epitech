/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/29
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef EX06_HPP
#define EX06_HPP

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

template<typename A, typename B = A>
class Tuple
{
public:
    Tuple() { }

    std::string toStr(const int a) const
    {
        std::string res("[int:");
        res += std::to_string(a);
        res += "]";
        return res;
    }

    std::string toStr(const float a) const
    {
        std::ostringstream out;
        out.precision(1);
        out << std::fixed << a;
        std::string res("[float:");
        res += out.str();
        res += "f]";
        return res;
    }

    std::string toStr(const std::string & a) const
    {
        std::string res("[string:\"");
        res += a;
        res += "\"]";
        return res;
    }

    template<typename C>
    std::string toStr(const C & a) const
    {
        return "[???]";
    }

    std::string toString() const
    {
        std::string res("[TUPLE ");
        res += toStr(a);
        res += " ";
        res += toStr(b);
        res += "]";
        return res;
    }

    A a;
    B b;
};

#endif // EX06_HPP
