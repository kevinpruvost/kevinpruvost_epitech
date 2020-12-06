
/*
** EPITECH PROJECT, 2020
** DLLoader.cpp
** File description:
** dyn lib loader
*/

#include "DLLoader.hpp"

// C++ includes
#include <iostream>

DLLoader::DLLoader(const std::string & libName)
    : _libName { libName }
{
    if ((_lib = dlopen(libName.c_str(), RTLD_NOW)) == NULL)
        throw EXCEPTION(libName + " cannot be loaded.");
}

DLLoader::~DLLoader()
{
    if (_lib)
        dlclose(_lib);
}

bool DLLoader::isError() const
{
    if (!_lib)
        std::cerr << "Error while loading \"" << _libName << "\" library.\n"
        << dlerror() << std::endl;
    return _lib == nullptr;
}