/*
** EPITECH PROJECT, 2020
** DLLoader.hpp
** File description:
** dlloader
*/

#pragma once

// Project includes
#include "Exception.hpp"

// C++ includes
#include <string>

// C includes
#include <dlfcn.h>
#include <memory>

class DLLoader
{
public:
    DLLoader(const std::string & libName);
    ~DLLoader();

    bool isError() const;

protected:
    void * _lib;
    const std::string _libName;
};
