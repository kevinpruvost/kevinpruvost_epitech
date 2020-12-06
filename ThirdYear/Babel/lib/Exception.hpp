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

#define EXCEPTION(msg) Exception(std::string(__FILE__)\
                       + ": line " + std::to_string(__LINE__) + ": " + msg)

/**
 * @brief Contains an appropriate std::exception constructor and a macro that have better ease of use.
 */
class Exception : virtual public std::exception
{
    public:
        explicit Exception(const std::string & message) : _msg{ message } {}
        virtual ~Exception() throw() {}

        const char * what() const throw() override { return _msg.c_str(); }

    private:
        const std::string _msg;
};

#undef  EXIT_FAILURE
#define EXIT_FAILURE 84
