/*
** EPITECH PROJECT, 2020
** Exception.cpp
** File description:
** exception
*/

#include "Exception.hpp"

#include <iostream>

Exception::Exception(const std::string & str)
    : _msg { str }
{
}

Exception::~Exception() throw()
{
}

const char * Exception::what() const throw()
{
    return _msg.c_str();
}