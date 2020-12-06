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

class Exception : virtual public std::exception
{
    public:
        explicit Exception(const std::string & message);
        virtual ~Exception() throw();

        const char * what() const throw() override;

    private:
        const std::string _msg;
};

#undef  EXIT_FAILURE
#define EXIT_FAILURE 84