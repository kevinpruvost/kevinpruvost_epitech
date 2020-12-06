/*
** EPITECH PROJECT, 2020
** ArcadeDLLoader.hpp
** File description:
** arcade dl loader hpp
*/

#pragma once

// Project includes
#include "ArcadeContent.hpp"
#include "Constants.hpp"
#include "Exception.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

// Project includes
#include "DLLoader.hpp"

template<class T>
class ArcadeDLLoader : virtual public DLLoader
{
public:
    ArcadeDLLoader(const std::string & libName);
    ~ArcadeDLLoader();

    T * getInstance(const std::string & funcName, ArcadeContent & arcadeContent) const;
};
