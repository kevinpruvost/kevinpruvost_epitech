/*
** EPITECH PROJECT, 2020
** Teddy.hpp
** File description:
** Teddy class declaration
*/

#pragma once

#include "Toy.hpp"

class Teddy : public Toy
{
    public:
    Teddy(const std::string & title);
    ~Teddy();

    public:
        void isTaken() override;

    private:
};