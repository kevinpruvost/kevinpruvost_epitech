/*
** EPITECH PROJECT, 2020
** Toy.hpp
** File description:
** Toy class declaration
*/

#pragma once

#include "Object.hpp"

class Toy : public Object
{
    public: 
        Toy(const std::string & title);
        ~Toy();
};