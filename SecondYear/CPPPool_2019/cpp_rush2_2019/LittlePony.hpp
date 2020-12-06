/*
** EPITECH PROJECT, 2020
** LittlePony.hpp
** File description:
** LittlePony class code
*/

#pragma once

#include "Toy.hpp"

class LittlePony : public Toy
{
    public:
        LittlePony(const std::string & title);
        ~LittlePony();
    
    public:
        void isTaken() override;
};