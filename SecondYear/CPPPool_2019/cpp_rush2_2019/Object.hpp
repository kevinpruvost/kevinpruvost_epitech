/*
** EPITECH PROJECT, 2020
** Object Class
** File description
** Object Class definition
*/

#pragma once

// C++ includes
#include <iostream>
#include <string>

class Object
{
    public:
        Object(const std::string & name = "");
        ~Object();

    public:
        std::string getName(void);
        void setName(const std::string & name);
        virtual void isTaken() = 0;
        bool isWrap();

    private:
        std::string _name;
};