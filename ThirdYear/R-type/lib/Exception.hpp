/*
** EPITECH PROJECT, 2020
** Exception.hpp
** File description:
** exception
*/

#pragma once

// C++ includes
#include <cassert>
#include <exception>
#include <string>
#include <sstream>

#define CRITICAL_EXCEPTION(msg) CriticalException("Critical Exception in " + std::string(__FILE__)\
                                    + ": line " + std::to_string(__LINE__) + ": " + msg)
#define MINOR_EXCEPTION(msg)    MinorException("Minor Exception in " + std::string(__FILE__)\
                                    + ": line " + std::to_string(__LINE__) + ": " + msg)

/**
 * @brief Contains an appropriate std::exception constructor and a macro that have better ease of use.
 */
class Exception : virtual public std::exception
{
public:
    explicit Exception(const std::string & message) : _msg{ message } {}
    virtual ~Exception() throw() {}

    const char * what() const throw() final override { return _msg.c_str(); }

private:
    const std::string _msg;
};

class CriticalException : virtual public Exception
{
public:
    explicit CriticalException(const std::string& msg) : Exception(msg) {}
    ~CriticalException() throw() {}
};

class MinorException : virtual public Exception
{
public:
    explicit MinorException(const std::string& msg) : Exception(msg) {}
    ~MinorException() throw() {}
};

#undef  EXIT_FAILURE
#define EXIT_FAILURE 84
